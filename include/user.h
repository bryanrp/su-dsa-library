#pragma once
#include <list>
#include <string>
#include "json.hpp"
using namespace std;

class User {
private:
    string name;
    string password;
    list<string> borrowed_books;

public:
    User(string _name, string _password);
    User(json::JSON obj);
    string get_name() const;
    list<string> get_borrowed_books() const;
    json::JSON get_json();

    bool check_password(string _password) const;
    void borrow_book(string isbn);
    bool return_book(string isbn);
};