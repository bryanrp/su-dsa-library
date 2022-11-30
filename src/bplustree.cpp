#pragma once
#include <vector>
#include "../include/bplustree.h"

template<typename K, typename V>
K BPlusTree<K, V>::get_minimum_key(Node *current) 
{
	if (current == nullptr)
	{
		assert(false);
	}
	
	while (current != nullptr && !current->is_leaf)
	{
		current = current->children[0];
	}
	
	if (current == nullptr)
	{
		assert(false);
	}
	
	return current->keys[0];
}

template<typename K, typename V>
bool BPlusTree<K, V>::is_exist_helper(Node *current, K key) const 
{
	if (current == nullptr)
	{
		return false;
	}
	
	if (current ->is_leaf)
	{
		for (int i = 0; i < current->cnt_key; i++)
		{
			if (key == current->keys[i])
			{
				return true;
			}
		}
		
		return false;
	}
	
	else
	{
		for (int i = 0; i < current->cnt_key; i++)
		{
			if (key < current->keys[i])
			{
				return is_exist_helper(current->children[i], key);
			}
		}
		
		return is_exist_helper(current->children[current->cnt_key], key);
	}
}

template<typename K, typename V>
V* BPlusTree<K, V>::get_value_helper(Node *current, K key) const 
{
	if (current == nullptr)
	{
		return nullptr;
	}
	
	if (current->is_leaf)
	{
		for (int i=0; i<current->cnt_key; i++)
		{
			if (current->keys[i]==key)
			{
				return current->values[i];
			}
		}
		return nullptr;
	}
	
	for (int i = 0; i < current->cnt_key; i++)
	{
		if (key < current->keys[i])
		{
			return get_value_helper(current->children[i], key);
		}
	}
	
	return get_value_helper(current->children[current->cnt_key], key);
}

template<typename K, typename V>
vector<V*> BPlusTree<K, V>::get_all_values_helper() const
{
	vector<V*> result;
	Node *current = root;
	while (!current->is_leaf)
	{
		current = current->children[0];
	}
	
	while (current != nullptr)
	{
		for (int i = 0, i < current->cnt_key; i++)
		{
			result.push_back(current->values[i]);
		}
		current = current->next_leaf;
	}
	return result;
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
    if (current == nullptr) { // unexpected case
        assert(false);
    }

    if (current->is_leaf) {
        int position = current->get_insert_position(key);
        if (position >= current->cnt_key || current->keys[position] != key) { // no such key
            return false;
        }
        remove_fix(current, key);
        return true;
    }
    else {
        for (int i = 0; i < current->cnt_key; i++) {
            if (key < current->keys[i]) {
                return remove_helper(current->children[i], key);
            }
        }
        return remove_helper(current->children[current->cnt_key], key);
    }
}

template<typename K, typename V>
void BPlusTree<K, V>::steal_left(Node *current, Node *left) {
    if (current->parent != left->parent || current->parent == nullptr) {
        assert(false);
    }

    K left_key = left->keys[left->cnt_key-1];
    V *left_value = left->values[left->cnt_key-1];
    Node *left_child = left->children[left->cnt_key];
    left->remove(left->cnt_key-1);

    int position_parent = 0;
    Node *p = current->parent;
    for (int i = 0; i < p->cnt_key; i++) {
        if (left == p->children[i]) {
            position_parent = i;
            break;
        }
    }
    K p_key = p->keys[position_parent];

    p->keys[position_parent] = left_key; // fix the parent keys
    if (current->is_leaf) current->insert(left_key, left_value, left_child, current->children[0]);
    else {
        current->insert(p_key, nullptr, left_child, current->children[0]);
        left_child->parent = current;
    }
}

template<typename K, typename V>
void BPlusTree<K, V>::steal_right(Node *current, Node *right) {
    if (current->parent != right->parent || current->parent == nullptr) {
        assert(false);
    }

    K right_key = right->keys[0];
    V *right_value = right->values[0];
    Node *right_child = right->children[0];
    right->remove(0, true);

    int position_parent = 0;
    Node *p = current->parent;
    for (int i = 0; i < p->cnt_key; i++) {
        if (current == p->children[i]) {
            position_parent = i;
            break;
        }
    }
    K p_key = p->keys[position_parent];

    if (current->is_leaf) p->keys[position_parent] = right->keys[0];
    else p->keys[position_parent] = right_key;
    // no need to fix p->keys[position_parent - 1] since if we need to fix it, then it will be fixed later by insert_fix
    if (current->is_leaf) current->insert(right_key, right_value, current->children[0], right_child);
    else {
        current->insert(p_key, nullptr, current->children[current->cnt_key], right_child);
        right_child->parent = current;
    }
}

template<typename K, typename V>
void BPlusTree<K, V>::merge(Node *left, Node *right) {
    if (left->parent != right->parent || left->parent == nullptr) {
        assert(false);
    }

    Node *p = left->parent;
    int parent_position;
    for (int i = 0; i < p->cnt_key; i++) {
        if (p->children[i] == left) {
            assert(p->children[i+1] == right);
            parent_position = i;
            break;
        }
    }
    K temp_key = p->keys[parent_position];
    p->remove(parent_position);

    Node *merged_node = new Node(degree);
    merged_node->parent = p;
    merged_node->is_leaf = left->is_leaf;

    if (merged_node->is_leaf) {
        merged_node->prev_leaf = left->prev_leaf;
        merged_node->next_leaf = right->next_leaf;
        if (left->prev_leaf != nullptr) left->prev_leaf->next_leaf = merged_node;
        if (right->next_leaf != nullptr) right->next_leaf->prev_leaf = merged_node;
    }

    for (int i = 0; i < left->cnt_key; i++) {
        merged_node->insert(left->keys[i], left->values[i], left->children[i], left->children[i+1]);
        if (!merged_node->is_leaf) {
            left->children[i]->parent = merged_node;
            left->children[i+1]->parent = merged_node;
        }
    }
    if (!merged_node->is_leaf) {
        merged_node->insert(temp_key, nullptr, left->children[left->cnt_key], right->children[0]);
        left->children[left->cnt_key]->parent = merged_node; // might be left out.
        right->children[0]->parent = merged_node; // might be left out. ex: when right->cnt_key = 0, then the next loops won't be run
    }
    for (int i = 0; i < right->cnt_key; i++) {
        merged_node->insert(right->keys[i], right->values[i], right->children[i], right->children[i+1]);
        if (!merged_node->is_leaf) {
            right->children[i]->parent = merged_node;
            right->children[i+1]->parent = merged_node;
        }
    }

    p->children[parent_position] = merged_node;
}

template<typename K, typename V>
void BPlusTree<K, V>::remove_fix(Node *current, K key) {
    if (current == nullptr) {
        assert(false);
    }

    while (current != nullptr) {
        int position = current->get_insert_position(key);
        if (current == root) {
            if (current->is_leaf) {
                current->remove(position);
            }
            else {
                if (current->cnt_key == 0) {
                    assert(current->children[0] != nullptr);
                    root = current->children[0];
                }
            }
            break;
        }
        else {
            if (position < current->cnt_key && key == current->keys[position]) { // key exists
                if (current->is_leaf) {
                    current->remove(position);
                    if (current->cnt_key < (degree-1)/2) { // underflow, need to fix
                        Node *left_sibling = current->get_left_sibling();
                        Node *right_sibling = current->get_right_sibling();
                        if (left_sibling != nullptr && left_sibling->cnt_key > (degree-1)/2) {
                            steal_left(current, left_sibling);
                        }
                        else if (right_sibling != nullptr && right_sibling->cnt_key > (degree-1)/2) {
                            steal_right(current, right_sibling);
                        }
                        else if (left_sibling != nullptr) { // merge with left sibling
                            merge(left_sibling, current);
                        }
                        else if (right_sibling != nullptr) { // merge with right sibling
                            merge(current, right_sibling);
                        }
                        else {
                            assert(false);
                        }
                    }
                }
                else {
                    // uncomment to avoid nonexistent key in internal node
                    // current->keys[position] = get_minimum_key(current->children[position+1]);
                }
            }

            if (!current->is_leaf && current->cnt_key < (degree-1)/2) {
                Node *left_sibling = current->get_left_sibling();
                Node *right_sibling = current->get_right_sibling();
                if (left_sibling != nullptr && left_sibling->cnt_key > (degree-1)/2) {
                    steal_left(current, left_sibling);
                }
                else if (right_sibling != nullptr && right_sibling->cnt_key > (degree-1)/2) {
                    steal_right(current, right_sibling);
                }
                else if (left_sibling != nullptr) { // merge with left sibling
                    merge(left_sibling, current);
                }
                else if (right_sibling != nullptr) {
                    merge(current, right_sibling);
                }
                else {
                    assert(false);
                }
            }
        }
        current = current->parent;
    }
}

template<typename K, typename V>
vector<V*> BPlusTree<K, V>::get_all_values_helper() const {

}

template<typename K, typename V>
void BPlusTree<K, V>::print_helper(Node *current, string space) {

}

template<typename K, typename V>
BPlusTree<K, V>::BPlusTree(int_degree)
{
	degree = _degree;
	size = 0;
	root = new Node (degree);
	root->is_leaf = true;
}

template<typename K, typename V>
BPlusTree<K, V>::BPlusTree(int _degree) {

}

template<typename K, typename V>
int BPlusTree<K, V>::get_size() const 
{
	return size;
}

template<typename K, typename V>
bool BPlusTree<K, V>::is_exist(K key) const 
{
	return is_exist_helper(root, key);
}

template<typename K, typename V>
V* BPlusTree<K, V>::get_value(K key) const 
{
	return get_value_helper(root, key);
}

template<typename K, typename V>
vector<V*> BPlusTree<K, V>::get_all_values() const
{
	return get_all_values_helper();
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
    if (remove_helper(root, key)) {
        size--;
        return true;
    }
    else {
        return false;
    }
}

template<typename K, typename V>
vector<V*> BPlusTree<K, V>::get_all_values() const {

}

template<typename K, typename V>
void BPlusTree<K, V>::print() {

}
