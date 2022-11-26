#pragma once
#include "../include/book.h"
using namespace std;

Book::Book() {

}

Book::Book(const Book& book) {

}

Book::Book(int _serial, string _name, int _num_of_available_books = 0, int _num_of_borrowed_books = 0) {

}

Book::Book(json::JSON obj) {

}

int Book::get_serial() const {

}

string Book::get_name() const {

}

int Book::get_num_of_available_books() const {

}

int Book::get_num_of_borrowed_books() const {

}

json::JSON Book::get_json() const {

}

void Book::set_serial(int _serial) {

}

void Book::set_name(string _name) {

}

void Book::set_num_of_available_books(int _num_of_available_books) {

}

void Book::set_num_of_borrowed_books(int _num_of_borrowed_books) {

}

void Book::add_book_stock(int amount) {

}

bool Book::remove_available_book_stock(int amount) {

}

bool Book::borrow_book(int amount) {

}

bool Book::return_book(int amount) {

}
