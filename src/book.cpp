#pragma once
#include "../include/book.h"
using namespace std;

Book::Book() {
    
}

Book::Book(const Book& book) {
    
}

Book::Book(json::JSON obj) {
    
}

string Book::get_isbn() const {
    
}

string Book::get_title() const {
    
}

string Book::get_author() const {
    
}

string Book::get_publisher() const {
    
}

int Book::get_year() const {
    
}

int Book::get_num_of_available_books() const {
    
}

int Book::get_num_of_borrowed_books() const {
    
}

json::JSON Book::get_json() const {
    
}

void Book::set_isbn(string _isbn) {
    
}

void Book::set_title(string _title) {
    
}

void Book::set_author(string _author) {
    
}

void Book::set_publisher(string _publisher) {
    
}

void Book::set_year(int _year) {
    
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
