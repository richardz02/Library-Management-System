#include <iostream>
#include <string>
#include <optional>
#include <unordered_map>
#include "book.hpp"

#ifndef LIBRARY_H_
#define LIBRARY_H_

class Library {
private:
        // Use a map to store the (isbn : title) key value pairs for now
        std::unordered_map<std::string, std::string> map;

public:
        Library() {}

        void add_book(std::string isbn, std::string title, std::string author, std::string publication_date);

        void delete_book(std::string isbn);

        std::optional<std::string> search_by_isbn(std::string isbn);
};


#endif // LIBRARY_H_
