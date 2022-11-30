#pragma once
#include "../include/user.h"

User::User(string _name, string _password) {
    name = _name;
    password = _password;
    borrowed_books = list<string>();
}

User::User(json::JSON obj) {
    name = obj["name"].ToString();
    password = obj["password"].ToString();
    for (int i = 0; i < obj["book"].size(); i++) {
        borrowed_books.push_back(obj["book"][i].ToString());
    }
}

string User::get_name() const {
    return name;
}

list<string> User::get_borrowed_books() const {
    return borrowed_books;
}

json::JSON User::get_json() {
    json::JSON obj;
    obj["name"] = name;
    obj["password"] = password;
    obj["book"] = json::Array();
    for (list<string>::iterator it = borrowed_books.begin(); it != borrowed_books.end(); it++) {
        obj["book"].append(*it);
    }
    return obj;
}

bool User::check_password(string _password) const {
    return password == _password;
}

void User::borrow_book(string isbn) {
    borrowed_books.push_back(isbn);
}

bool User::return_book(string isbn) {
    for (list<string>::iterator it = borrowed_books.begin(); it != borrowed_books.end(); it++) {
        if (*it == isbn) {
            borrowed_books.erase(it);
            return true;
        }
    }
    return false;
}