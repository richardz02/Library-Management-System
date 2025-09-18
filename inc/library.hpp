#include <iostream>
#include <string>
#include <optional>
#include <pqxx/pqxx>
#include "book.hpp"

#ifndef LIBRARY_H_
#define LIBRARY_H_

class Library {
    pqxx::connection conn;

public:
        // Initialize a connection to the database in the constructor
        Library(const std::string& connection_info) : conn(connection_info) {}

        // Book operations
        void add_book(const Book& book);
        void search_by_isbn(std::string isbn);
        void delete_book(std::string isbn);
        void display_all_books();

        // Copy operations
        void insert_copy(const std::string& isbn, int available_copies);
        void update_copy(int copy_id, const std::string& new_status);
        void remove_copy(int copy_id);
        void display_copies_by_isbn(const std::string& isbn);
        void display_all_copies();
};


#endif // LIBRARY_H_
