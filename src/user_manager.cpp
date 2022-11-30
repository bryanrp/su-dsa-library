#pragma once
#include <cassert>
#include <fstream>
#include <sstream>
#include "../include/user_manager.h"
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

User UserManager::get_user_by_name(string name) const {
    if (data.is_exist(name)) {
        return User(*data.get_value(name));
    }
    else {
        return User("", "", "");
    }
}

vector<User> UserManager::get_all_users() const {
    vector<User*> user_ori = data.get_all_values();
    vector<User> user_copy;
    for (int i = 0; i < user_ori.size(); i++) {
        user_copy.push_back(User(*user_ori[i]));
    }
    return user_copy;
}

bool UserManager::register_user(string name, string password, string phone) {
    if (data.is_exist(name)) {
        return false;
    }
    else {
        return data.insert(name, User(name, password, phone));
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

bool UserManager::update_user(string name, User user) {
    if (!data.is_exist(name)) {
        return false;
    }
    else {
        assert(name == user.get_name());
        User *user_ori = data.get_value(name);
        user_ori->set_password(user.get_password());
        user_ori->set_phone(user.get_phone());
        return true;
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