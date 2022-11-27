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

}

template<typename K, typename V>
void BPlusTree<K, V>::insert_fix(Node *current, K key, V *value) {

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
