#pragma once
#include <vector>
#include <string>
using namespace std;

template <typename K, typename V>
class BPlusTree {
private:
    class Node {
    public:
        
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