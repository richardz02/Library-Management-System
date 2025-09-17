#include "../inc/library.hpp"
#include <exception>

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
