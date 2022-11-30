#pragma once
#include <string>
#include "user.h"
#include "bplustree.h"
using namespace std;

class UserManager {
private:
    BPlusTree<string, User> data;
public:
    UserManager(const string &file_location);
    void load_data(const string &file_location);
    void save_data(const string &file_location);

    vector<User> get_all_users() const;

    bool register_user(string name, string password);
    bool login_user(string name, string password) const;

    vector<string> get_borrowed_books(string name) const;
    bool borrow_book(string name, string isbn);
    bool return_book(string name, string isbn);
};