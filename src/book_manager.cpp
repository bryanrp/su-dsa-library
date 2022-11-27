#pragma once
#include "../include/book_manager.h"
#include "bplustree.cpp"
#include "book.cpp"
using namespace std;

BookManager::BookManager() {
    
}

BookManager::BookManager(const string& file_location) {
    
}

void BookManager::load_data(const string& file_location) {

}

void BookManager::save_data(const string& file_location) {
    
}

int BookManager::get_num_of_books() {
    
}

vector<Book> BookManager::get_all_books() const {
    
}

Book BookManager::get_book_by_isbn(string isbn) const {
    
}

bool BookManager::create_book(const Book& book) {
    
}

bool BookManager::update_book(string old_isbn, const Book& book) {
    
}

bool BookManager::delete_book(string isbn) {
    
}

bool BookManager::add_book_stock(string isbn, int amount) {
    
}

bool BookManager::remove_book_stock(string isbn, int amount) {
    
}

bool BookManager::borrow_book(string isbn, int amount) {
    
}

bool BookManager::return_book(string isbn, int amount) {
    
}