#include <iostream>
#include "../inc/book_management_system.hpp"

#ifndef CLI_HPP
#define CLI_HPP

class CLI {
    Book_Management_System bms;

    // Displays a menu for the user to choose from
    void display_menu();

    // Adds book to library
    void add_book();

    // Deletes a book from library
    void delete_book();

    // Searches a book either by id or by title
    void search_book();

    public:
        // To run the cli application
        void run();
};

#endif // CLI_HPP
