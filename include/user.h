#pragma once
#include <list>
#include <string>
#include "json.hpp"
using namespace std;

class User {
private:
    string name;
    string password;
    string phone;
    list<string> borrowed_books;

public:
    User(const User &user);
    User(string _name, string _password, string  _phone);
    User(json::JSON obj);
    string get_name() const;
    string get_password() const;
    string get_phone() const;
    list<string> get_borrowed_books() const;
    json::JSON get_json();

    void set_password(string new_password);
    void set_phone(string new_phone);

    bool check_password(string _password) const;
    void borrow_book(string isbn);
    bool return_book(string isbn);
};