#include <iostream>
#include <string>
#include <optional>
#include <pqxx/pqxx>
#include "book.hpp"

#ifndef LIBRARY_H_
#define LIBRARY_H_

class Library {
private:
        pqxx::connection conn;

public:
        // Initialize a connection to the database in the constructor
        Library(const std::string& connection_info) : conn(connection_info) {}

        /* ---------------Book operations---------------- */

        /**
         * @brief Adds new book to the library
         *
         * This function takes in a vector array of strings which contains information about the book to be added to the library
         *
         * args is expected to have:
         * args[0] = ISBN
         * args[1] = Title
         * args[2] = Author
         * args[3] = Publication Date
         */
        void add_book(const std::vector<std::string>& args);

        /**
         * @brief Searches for a book by ISBN
         *
         * This function takes in a vector array of a string which is the ISBN of the book to be searched
         *
         * args is expected to have:
         * args[0] = ISBN
         */
        void search_by_isbn(const std::vector<std::string>& args);

        /**
         * @brief Deletes a book by ISBN
         *
         * This function takes in a vector array of a string which is the ISBN of the book to be deleted
         *
         * args is expected to have:
         * args[0] = ISBN
         */
        void delete_book(const std::vector<std::string>& args);

        /**
         * @brief Displays all books in the library
         *
         * This function displays all books and their metadata stored in the library, does not expect args
         */
        void display_all_books(const std::vector<std::string>& args);

        /* ------------Copy Operations------------------ */

        /**
         * @brief Inserts copies of a book into the library
         *
         * This function takes in a vector array of strings which contains the ISBN of a book and number of copies
         *
         * args is expected to have:
         * args[0] = ISBN
         * args[1] = Number of copies
         */
        void insert_copy(const std::vector<std::string>& args);

        /**
         * @brief Updates the status of a copy of a book
         *
         * This function takes in a vector array of strings which contains the copy id of the book, and new status
         *
         * args is expected to have:
         * args[0] = Copy ID
         * args[1] = New status
         */
        void update_copy(const std::vector<std::string>& args);

        /**
         * @brief Removes a copy of a book from the library
         *
         * This function takes in a vector array of a string which is the copy id of the copy to be removed
         *
         * args is expected to have:
         * args[0] = Copy ID
         */
        void remove_copy(const std::vector<std::string>& args);

        /**
         * @brief Displays all copies of books in the library
         *
         * This function prints all copies of books in the library, does not expect args
         */
        void display_all_copies(const std::vector<std::string>& args);

        // Other operations
        void help(const std::vector<std::string>& args);
        void exit_program(const std::vector<std::string>& args);
};


#endif // LIBRARY_H_
