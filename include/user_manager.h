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

    User get_user_by_name(string name) const;
    vector<User> get_all_users() const;

    bool register_user(string name, string password, string phone);
    bool login_user(string name, string password) const;
    bool update_user(string name, User user);

    bool borrow_book(string name, string isbn);
    bool return_book(string name, string isbn);
};