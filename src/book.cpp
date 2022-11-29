#pragma once
#include "../include/book.h"
using namespace std;

Book::Book() {
    isbn = "";
    title = "";
    author = "";
    publisher = "";
    year = -9999;
    num_of_available_books = -1;
    num_of_borrowed_books = -1;
}

Book::Book(const Book& book) {
    isbn = book.isbn;
    title = book.title;
    author = book.author;
    publisher = book.publisher;
    year = book.year;
    num_of_available_books = book.num_of_available_books;
    num_of_borrowed_books = book.num_of_borrowed_books;
}

Book::Book(json::JSON obj) {
    
}

string Book::get_isbn() const {
    return isbn;
}

string Book::get_title() const {
    return title;
}

string Book::get_author() const {
    return author;
}

string Book::get_publisher() const {
    return publisher;
}

int Book::get_year() const {
    return year;
}

int Book::get_num_of_available_books() const {
    return num_of_available_books;
}

int Book::get_num_of_borrowed_books() const {
    return num_of_borrowed_books;
}

json::JSON Book::get_json() const {
    
}

void Book::set_isbn(string _isbn) {
    isbn = _isbn;
}

void Book::set_title(string _title) {
    title = _title;
}

void Book::set_author(string _author) {
    author = _author;
}

void Book::set_publisher(string _publisher) {
    publisher = _publisher;
}

void Book::set_year(int _year) {
    year = _year;
}

void Book::set_num_of_available_books(int _num_of_available_books) {
    num_of_available_books = _num_of_available_books;
}

void Book::set_num_of_borrowed_books(int _num_of_borrowed_books) {
    num_of_borrowed_books = _num_of_borrowed_books;
}

void Book::add_book_stock(int amount) {
    num_of_available_books += amount;
}

bool Book::remove_available_book_stock(int amount) {
    if (num_of_available_books - amount >= 0) {
        num_of_available_books -= amount;
        return true;
    }
    else {
        return false;
    }
}

bool Book::borrow_book(int amount) {
    if (num_of_available_books - amount >= 0) {
        num_of_available_books -= amount;
        num_of_borrowed_books += amount;
        return true;
    }
    else {
        return false;
    }
}

bool Book::return_book(int amount) {
    if (num_of_borrowed_books - amount >= 0) {
        num_of_borrowed_books -= amount;
        num_of_available_books += amount;
        return true;
    }
    else {
        return false;
    }
}