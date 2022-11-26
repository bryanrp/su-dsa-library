#pragma once
#include <fstream>
#include <sstream>
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

Book BookManager::get_book_by_serial(int serial) const {

}

bool BookManager::create_book(const Book& book) {

}

bool BookManager::add_book_stock(int serial, int amount) {

}

bool BookManager::delete_book(int serial) {

}

bool BookManager::remove_book_stock(int serial, int amount) {

}

bool BookManager::update_book(int old_serial, const Book& book) {

}

bool BookManager::borrow_book(int serial, int amount) {

}

bool BookManager::return_book(int serial, int amount) {

}
