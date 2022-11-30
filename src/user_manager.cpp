#pragma once
#include <cassert>
#include <fstream>
#include <sstream>
#include "../include/user_manager.h"
#include "bplustree.cpp"
#include "user.cpp"

UserManager::UserManager(const string &file_location) {
    load_data(file_location);
}

void UserManager::load_data(const string &file_location) {
    data = BPlusTree<string, User>();
    ifstream input(file_location);
    stringstream buffer;
    buffer << input.rdbuf();
    json::JSON obj = json::JSON::Load(buffer.str());

    for (int i = 0; i < obj.length(); i++) {
        data.insert(obj[i]["name"].ToString(), User(obj[i]));
    }
}

void UserManager::save_data(const string &file_location) {
    json::JSON obj = json::Array();
    vector<User> users = get_all_users();
    for (int i = 0; i < users.size(); i++) {
        obj.append(users[i].get_json());
    }
    ofstream output(file_location);
    output << obj.dump();
}

vector<User> UserManager::get_all_users() const {
    vector<User*> user_ori = data.get_all_values();
    vector<User> user_copy;
    for (int i = 0; i < user_ori.size(); i++) {
        user_copy.push_back(User(*user_ori[i]));
    }
    return user_copy;
}

bool UserManager::register_user(string name, string password) {
    if (data.is_exist(name)) {
        return false;
    }
    else {
        return data.insert(name, User(name, password));
    }
}

bool UserManager::login_user(string name, string password) const {
    if (!data.is_exist(name)) {
        return false;
    }
    else {
        User *user = data.get_value(name);
        return user->check_password(password);
    }
}

vector<string> UserManager::get_borrowed_books(string name) const {
    if (!data.is_exist(name)) {
        return vector<string>();
    }
    else {
        User *user = data.get_value(name);
        if (user == nullptr) {
            assert(false);
        }
        else {
            list<string> borrowed_books = user->get_borrowed_books();
            vector<string> result;
            for (list<string>::iterator it = borrowed_books.begin(); it != borrowed_books.end(); it++) {
                result.push_back(*it);
            }
            return result;
        }
    }
}

bool UserManager::borrow_book(string name, string isbn) {
    if (!data.is_exist(name)) {
        return false;
    }
    else {
        User *user = data.get_value(name);
        if (user == nullptr) {
            assert(false);
        }
        else {
            user->borrow_book(isbn);
            return true;
        }
    }
}

bool UserManager::return_book(string name, string isbn) {
    if (!data.is_exist(name)) {
        return false;
    }
    else {
        User *user = data.get_value(name);
        if (user == nullptr) {
            assert(false);
        }
        else {
            return user->return_book(isbn);
        }
    }
}