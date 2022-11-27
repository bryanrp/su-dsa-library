#pragma once
#include <vector>
#include <string>
using namespace std;

template <typename K, typename V>
class BPlusTree {
private:
    class Node {
    public:
        int m;
        int cnt_key;
        Node *parent;
        K *keys;
        Node **children;
        V **values;
        bool is_leaf;
        Node *next_leaf;
        Node *prev_leaf;

        Node(int _m) {
            m = _m;
            parent = nullptr;

            cnt_key = 0;
            keys = new K[m]; // only need m-1. this is to simplify split operation
            values = new V*[m]; // only need m-1. this is to simplify split operation
            children = new Node*[m+1]; // only need m. to simplify several operations

            for (int i = 0; i < m; i++) keys[i] = K();
            for (int i = 0; i < m; i++) values[i] = nullptr;
            for (int i = 0; i < m+1; i++) children[i] = nullptr;

            is_leaf = false;
            next_leaf = nullptr;
            prev_leaf = nullptr;
        }

        // return the position of the to be inserted key. or the position of the first key that is >= key argument
        int get_insert_position(K key) {
            int position = 0;
            while (position < cnt_key && key > keys[position]) {
                position++;
            }
            return position;
        }

        // assuming cnt_key < m
        void insert(K key, V* value, Node *left_child, Node *right_child) {
            if (cnt_key >= m) { // unexpected case
                assert(false);
            }

            int position = get_insert_position(key);

            for (int i = cnt_key; i > position; i--) {
                keys[i] = keys[i-1];
                if (is_leaf) {
                    values[i] = values[i-1];
                }
                else {
                    children[i+1] = children[i];
                }
            }

            keys[position] = key;
            if (is_leaf) {
                values[position] = value;
            }
            else {
                children[position] = left_child;
                children[position+1] = right_child;
            }
            cnt_key++;
        }

        // delete_left_child means that we delete children[position]. if set to false, then we delete children[position+1]
        // delete_left_child = true only called by steal_right()
        void remove(int position, bool delete_left_child = false) {
            if (position == 0) delete_left_child = true;
            for (int i = position; i < cnt_key - 1; i++) {
                keys[i] = keys[i+1];
                if (is_leaf) {
                    values[i] = values[i+1];
                }
                else {
                    if (delete_left_child) children[i] = children[i+1];
                    else children[i+1] = children[i+2];
                }
            }
            if (delete_left_child) children[cnt_key-1] = children[cnt_key];

            values[cnt_key - 1] = nullptr;
            children[cnt_key] = nullptr;
            cnt_key--;
        }

        Node* get_left_sibling() { // return nullptr if not exist
            if (parent == nullptr) {
                return nullptr;
            }

            Node *p = parent;
            for (int i = 1; i <= p->cnt_key; i++) {
                if (p->children[i] == this) {
                    return p->children[i-1];
                }
            }
            return nullptr;
        }

        Node* get_right_sibling() { // return nullptr if not exist
            if (parent == nullptr) {
                return nullptr;
            }

            Node *p = parent;
            for (int i = 0; i < p->cnt_key; i++) {
                if (p->children[i] == this) {
                    return p->children[i+1];
                }
            }
            return nullptr;
        }
    };

    int degree;
    int size;
    Node *root;
    
    K get_minimum_key(Node *current);
    bool is_exist_helper(Node *current, K key) const;
    V* get_value_helper(Node *current, K key) const;
    vector<V*> get_all_values_helper() const;

    void print_helper(Node *current, string space);

    void insert_fix(Node *current, K key, V *value);
    bool insert_helper(Node *current, K key, V *value); // return true if operation successful

    // three helper functions for remove_fix
    void steal_left(Node *current, Node *left);
    void steal_right(Node *current, Node *right);
    void merge(Node *left, Node *right);

    void remove_fix(Node *current, K key);
    bool remove_helper(Node *current, K key);

public:
    BPlusTree(int _degree = 3);
    int get_size() const;
    bool is_exist(K key) const;
    V* get_value(K key) const;
    vector<V*> get_all_values() const;
    bool insert(K key, const V &value);
    bool remove(K key);
    void print();
};