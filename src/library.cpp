#include <exception>
#include <iomanip>
#include <ios>
#include <string>
#include <vector>
#include "../inc/library.hpp"

void Library::add_book(const std::vector<std::string>& args) {
    // Validate inputs
    if (args.size() != 4) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: add-book <isbn> <title> <author> <pub. date>\n";
        return;
    }

    // Extract isbn, title, author, and pub date from args
    std::string isbn = args[0];
    std::string title = args[1];
    std::string author = args[2];
    std::string publication_date = args[3];

    try {
        pqxx::work tx(conn_);

        /**
         * Insert new book into the library catalog
         *
         * books table has the following fields:
         * - isbn: uniquely identify each book
         * - title
         * - author
         * - publication date
         */
        pqxx::params p;
        p.append(isbn);
        p.append(title);
        p.append(author);
        p.append(publication_date);

        tx.exec(
            "INSERT INTO books (isbn, title, author, publication_date) VALUES ($1, $2, $3, $4)", p
        );
        tx.commit();
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void Library::search_by_isbn(const std::vector<std::string>& args) {
    // Validate inputs
    if (args.size() != 1) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: search-book <isbn>\n";
        return;
    }

    // Extract isbn from args
    std::string isbn = args[0];

    try {
        pqxx::work tx(conn_);

        pqxx::params p;
        p.append(isbn);

        pqxx::result r = tx.exec("SELECT title, author, publication_date FROM books WHERE isbn = " + tx.quote(isbn));

        // If the result came back empty, return message that book does not exist
        if (r.empty()) {
            std::cout << "Book does not exist." << std::endl;
            return;
        } else {
            auto row = r[0];

            std::cout << "Title: " << row["title"].as<std::string>() << std::endl;
            std::cout << "Author: " << row["author"].as<std::string>() << std::endl;
            std::cout << "Publication Date: " << row["publication_date"].as<std::string>() << std::endl;
        }
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void Library::delete_book(const std::vector<std::string>& args) {
    // Validate inputs
    if (args.size() != 1) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: delete-book <isbn>\n";
        return;
    }

    // Extract isbn from args
    std::string isbn = args[0];

    try {
        pqxx::work tx(conn_);

        pqxx::params p;
        p.append(isbn);

        tx.exec("DELETE FROM books WHERE isbn = " + tx.quote(isbn));
        tx.commit();
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void Library::list_all_books(const std::vector<std::string>& args) {
    if (!args.empty()) {
        std::cout << "Invalid command.\n";
        std::cout << "list-books does not expect any arguments";
    }


    try {
        pqxx::read_transaction tx(conn_);

        pqxx::result r = tx.exec("SELECT * FROM books");

        if (r.empty()) {
            std::cout << "Library is empty." << std::endl;
            return;
        } else {
            // Print header
            std::cout << std::left
                << std::setw(15) << "ISBN"
                << std::setw(25) << "Title"
                << std::setw(25) << "Author"
                << std::setw(12) << "Pub. Date"
                << "\n";
            std::cout << std::string(80, '-') << "\n";

            // Iterate through all the records returned and display them
            for (auto row : r) {
                std::cout << std::left
                    << std::setw(15) << row["isbn"].as<std::string>()
                    << std::setw(25) << row["title"].as<std::string>()
                    << std::setw(25) << row["author"].as<std::string>()
                    << std::setw(12) << row["publication_date"].as<std::string>()
                    << "\n";
            }
        }
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void Library::insert_copy(const std::vector<std::string>& args) {
    // Validate inputs
    if (args.size() != 2) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: insert-copy <isbn> <count>\n";
        return;
    }

    // Extract isbn and number of available copies from args
    std::string isbn = args[0];
    int available_copies = std::stoi(args[1]);

    try {
        pqxx::work tx(conn_);

        /**
         * Insert a number of copies of a book into the library
         *
         * copies table has the following fields:
         * - copy_id: automatically set by postgres, uniquely identify each copy
         * - isbn: foreign key reference to books table
         * - status: available, checked-out, damaged, lost
         */
        pqxx::params p;
        p.append(isbn);

        for (int i = 0; i < available_copies; i++) {
            tx.exec("INSERT INTO copies (isbn) VALUES ($1)", p);
        }
        tx.commit();
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void Library::update_copy(const std::vector<std::string>& args) {
    // Validate inputs
    if (args.size() != 2) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: update-copy <copy_id> <status>\n";
        return;
    }

    // Extract copy id and new status from args
    int copy_id = std::stoi(args[0]);
    std::string new_status = args[1];

    // Before updating the status of a copy, check the status is one of the following:
    // available, checked-out, damaged, lost
    if (new_status != "available" && new_status != "checked-out" && new_status != "lost" && new_status != "damaged") {
        std::cout << "Invalid status. Status options are: available, checked-out, lost, damaged.\n";
        return;
    }

    try {
        pqxx::work tx(conn_);

        // Update the status of a copy
        pqxx::params p;
        p.append(new_status);
        p.append(copy_id);

        tx.exec("UPDATE copies SET status = $1 WHERE copy_id = $2", p);
        tx.commit();
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void Library::remove_copy(const std::vector<std::string>& args) {
    // Validate inputs
    if (args.size() != 1) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: remove-copy <copy_id>\n";
        return;
    }

    // Extract copy id from args
    int copy_id = std::stoi(args[0]);

    try {
        pqxx::work tx(conn_);

        // Remove a specific copy from the library
        pqxx::params p;
        p.append(copy_id);

        tx.exec("DELETE FROM copies WHERE copy_id = $1", p);
        tx.commit();
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void Library::list_all_copies(const std::vector<std::string>& args) {
    // Validate inputs
    if (!args.empty()) {
        std::cout << "Invalid command.\n";
        std::cout << "list-copies does not expect any arguments.\n";
        return;
    }

    try {
        pqxx::read_transaction tx(conn_);

        pqxx::result r = tx.exec("SELECT books.isbn, title, author, publication_date, copy_id, status FROM books INNER JOIN copies on books.isbn = copies.isbn");

        if (r.empty()) {
            std::cout << "No copies exist.\n";
            return;
        }

        // Print header
        std::cout << std::left
            << std::setw(15) << "ISBN"
            << std::setw(25) << "Title"
            << std::setw(25) << "Author"
            << std::setw(12) << "Pub. Date"
            << std::setw(10) << "Copy ID"
            << std::setw(15) << "Status"
            << "\n";
        std::cout << std::string(100, '-') << "\n";

        // Iterate through all the records returned and display them
        for (auto row : r) {
            std::cout << std::left
                << std::setw(15) << row["isbn"].as<std::string>()
                << std::setw(25) << row["title"].as<std::string>()
                << std::setw(25) << row["author"].as<std::string>()
                << std::setw(12) << row["publication_date"].as<std::string>()
                << std::setw(10) << row["copy_id"].as<std::string>()
                << std::setw(15) << row["status"].as<std::string>()
                << "\n";
        }
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void Library::help(const std::vector<std::string> &args) {
    // Validate inputs
    if (!args.empty()) {
        std::cout << "Invalid command.\n";
        std::cout << "This command does not expect any arguments.\n";
        return;
    }

    int width = 50; // Width for the command column

    std::cout << "Library Management System - Help Menu" << std::endl;
    std::cout << "-------------------------------------" << std::endl << std::endl;

    std::cout << "Book operations:" << std::endl;
    std::cout << "  " << std::setw(width) << std::left << "add-book <isbn> <title> <author> <pub_date>"
         << "Add a new book to the catalog" << std::endl;
    std::cout << "  " << std::setw(width) << "search-book <isbn>"
         << "Search for a book by ISBN" << std::endl;
    std::cout << "  " << std::setw(width) << "delete-book <isbn>"
         << "Delete a book from the catalog" << std::endl;
    std::cout << "  " << std::setw(width) << "list-books"
         << "Display all books in the catalog" << std::endl << std::endl;

    std::cout << "Copy operations:" << std::endl;
    std::cout << "  " << std::setw(width) << "insert-copy <isbn> <count>"
         << "Add one or more copies" << std::endl;
    std::cout << "  " << std::setw(width) << "update-copy <copy_id> <status>"
         << "Update the status of a copy" << std::endl;
    std::cout << "  " << std::setw(width) << "remove-copy <copy_id>"
         << "Remove a copy from the system" << std::endl;
    std::cout << "  " << std::setw(width) << "list-copies"
         << "Display all copies" << std::endl << std::endl;

    std::cout << "User operations:" << std::endl;
    std::cout << "  " << std::setw(width) << "add-user <first name> <last name> <email>"
         << "Add new user" << std::endl;
    std::cout << "  " << std::setw(width) << "search-user <user_id>"
         << "Search for a user by user id" << std::endl;
    std::cout << "  " << std::setw(width) << "delete-user <user_id>"
         << "Remove a user from the system" << std::endl;
    std::cout << "  " << std::setw(width) << "list-users"
         << "Display all users" << std::endl << std::endl;

    std::cout << "Services:" << std::endl;
    std::cout << "  " << std::setw(width) << "checkout <copy_id> <user_id>"
         << "Allows user to check out a copy of a book" << std::endl;
    std::cout << "  " << std::setw(width) << "returning <copy_id> <user_id> <status>"
         << "Allows user to return a book with updated status of copy" << std::endl;
    std::cout << "  " << std::setw(width) << "view-borrow"
         << "Returns all active borrowing records" << std::endl;
    std::cout << "  " << std::setw(width) << "view-all-borrow"
         << "Returns entire list of borrowing records" << std::endl << std::endl;

    std::cout << "Other operations:" << std::endl;
    std::cout << "  " << std::setw(width) << "help"
         << "Show this help menu" << std::endl;
    std::cout << "  " << std::setw(width) << "exit"
         << "Exit the program" << std::endl;
};

void Library::exit_program(const std::vector<std::string> &args) {
    // Validate inputs
    if (!args.empty()) {
        std::cout << "Invalid command.\n";
        std::cout << "This command does not expect any arguments.\n";
        return;
    }

    // Exit program
    exit(0);
}
