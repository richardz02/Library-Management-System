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

        void add_book(const Book& book);
        void search_by_isbn(std::string isbn);
        void delete_book(std::string isbn);
};


#endif // LIBRARY_H_
