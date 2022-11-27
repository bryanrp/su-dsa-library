#pragma once
#include <vector>
#include "../include/bplustree.h"

template<typename K, typename V>
K BPlusTree<K, V>::get_minimum_key(Node *current) {

}

template<typename K, typename V>
bool BPlusTree<K, V>::is_exist_helper(Node *current, K key) const {

}

template<typename K, typename V>
V* BPlusTree<K, V>::get_value_helper(Node *current, K key) const {

}

// return true if operation successful
template<typename K, typename V>
bool BPlusTree<K, V>::insert_helper(Node *current, K key, V *value) {
    if (current == nullptr) { // unexpected case
        assert(false);
    }

    if (current->is_leaf) {
        insert_fix(current, key, value);
        return true;
    }
    else {
        for (int i = 0; i < current->cnt_key; i++) {
            if (key < current->keys[i]) {
                return insert_helper(current->children[i], key, value);
            }
        }
        return insert_helper(current->children[current->cnt_key], key, value);
    }
}

template<typename K, typename V>
void BPlusTree<K, V>::insert_fix(Node *current, K key, V *value) {
    if (current == nullptr || !current->is_leaf) { // unexpected case
        assert(false);
    }

    Node *next_left = nullptr;
    Node *next_right = nullptr;
    while (true) {
        if (current == nullptr) { // no parent, create new root node
            root = new Node(degree);
            root->insert(key, value, next_left, next_right);
            root->children[0]->parent = root;
            root->children[1]->parent = root;
            break;
        }
        else if (current->cnt_key == degree-1) { // need to fix
            Node *left, *right;
            left = new Node(degree);
            right = new Node(degree);
            left->parent = right->parent = current->parent;
            left->is_leaf = right->is_leaf = current->is_leaf;
            if (current->is_leaf) { // connecting the between-leaves linked list
                left->prev_leaf = current->prev_leaf;
                left->next_leaf = right;

                right->prev_leaf = left;
                right->next_leaf = current->next_leaf;

                if (current->prev_leaf != nullptr) current->prev_leaf->next_leaf = left;
                if (current->next_leaf != nullptr) current->next_leaf->prev_leaf = right;
            }

            current->insert(key, value, next_left, next_right);

            for (int i = 0; i < current->cnt_key/2; i++) {
                left->insert(current->keys[i], current->values[i], current->children[i], current->children[i+1]);
                if (!current->is_leaf) {
                    current->children[i]->parent = left;
                    current->children[i+1]->parent = left;
                }
            }
            for (int i = current->cnt_key/2 + (!current->is_leaf); i < current->cnt_key; i++) {
                right->insert(current->keys[i], current->values[i], current->children[i], current->children[i+1]);
                if (!current->is_leaf) {
                    current->children[i]->parent = right;
                    current->children[i+1]->parent = right;
                }
            }

            key = current->keys[current->cnt_key/2];
            next_left = left;
            next_right = right;
            current = current->parent;
        }
        else { // just_insert
            current->insert(key, value, next_left, next_right);
            break;
        }
    }
}

template<typename K, typename V>
bool BPlusTree<K, V>::remove_helper(Node *current, K key) {

}

template<typename K, typename V>
void BPlusTree<K, V>::steal_left(Node *current, Node *left) {

}

template<typename K, typename V>
void BPlusTree<K, V>::steal_right(Node *current, Node *right) {

}

template<typename K, typename V>
void BPlusTree<K, V>::merge(Node *left, Node *right) {

}

template<typename K, typename V>
void BPlusTree<K, V>::remove_fix(Node *current, K key) {

}

template<typename K, typename V>
vector<V*> BPlusTree<K, V>::get_all_values_helper() const {

}

template<typename K, typename V>
void BPlusTree<K, V>::print_helper(Node *current, string space) {

}

template<typename K, typename V>
BPlusTree<K, V>::BPlusTree(int _degree) {

}

template<typename K, typename V>
int BPlusTree<K, V>::get_size() const {

}

template<typename K, typename V>
bool BPlusTree<K, V>::is_exist(K key) const {

}

template<typename K, typename V>
V* BPlusTree<K, V>::get_value(K key) const {

}

template<typename K, typename V>
bool BPlusTree<K, V>::insert(K key, const V &value) {
    if (insert_helper(root, key, new V(value))) {
        size++;
        return true;
    }
    else {
        return false;
    }
}

template<typename K, typename V>
bool BPlusTree<K, V>::remove(K key) {

}

template<typename K, typename V>
vector<V*> BPlusTree<K, V>::get_all_values() const {

}

template<typename K, typename V>
void BPlusTree<K, V>::print() {

}
