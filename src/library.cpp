#include <exception>
#include <iomanip>
#include <ios>
#include "../inc/library.hpp"

/**
 * =============================
 *      Book Operations
 * =============================
 */

// Adding a book to the library
void Library::add_book(const Book& book) {
    try {
        pqxx::work tx(conn);

        pqxx::params p;
        p.append(book.isbn);
        p.append(book.title);
        p.append(book.author);
        p.append(book.publication_date);

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

// Search book by isbn, return book title
void Library::search_by_isbn(std::string isbn) {
    try {
        pqxx::work tx(conn);

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
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

// Deleting a book from the library
void Library::delete_book(std::string isbn) {
    try {
        pqxx::work tx(conn);

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

// Display all books in the library
void Library::display_all_books() {
    try {
        pqxx::read_transaction tx(conn);

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

/**
 * =========================
 *       Copy Operations
 * =========================
 */

// Insert a new copy of a book into the library
void Library::insert_copy(const std::string &isbn, int available_copies) {
    try {
        pqxx::work tx(conn);

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

// Update the status of a copy
void Library::update_copy(int copy_id, const std::string &new_status) {
    try {
        pqxx::work tx(conn);

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

// Remove a copy of a book
void Library::remove_copy(int copy_id) {
    try {
        pqxx::work tx(conn);

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

void Library::display_all_copies() {
    try {
        pqxx::read_transaction tx(conn);

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
