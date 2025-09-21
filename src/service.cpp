#include <iomanip>
#include <iostream>
#include "../inc/service.hpp"

void Service::checkout(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: checkout <copy_id> <user_id>\n";
        return;
    }

    // Extract copy id and user id from args
    int copy_id = std::stoi(args[0]);
    int user_id = std::stoi(args[1]);

    try {
        pqxx::work tx(conn_);

        /**
         * Insert the borrowing record into the borrow table
         *
         * borrow table has the following fields:
         * - borrow_id: automatically set by postgres
         * - copy_id: foreign key referencing copies table
         * - user_id: foreign key referencing users table
         * - borrow_date: automatically set by postgres when record is inserted in the database
         * - return_date: NULL is not yet returned
         */
        pqxx::params p;
        p.append(copy_id);
        p.append(user_id);

        tx.exec("INSERT INTO borrow (copy_id, user_id) VALUES ($1, $2)", p);

        // Update the copies table to change status of the copy from "available" to "checked-out"
        pqxx::params p2;
        p2.append("checked-out");
        p2.append(copy_id);

        tx.exec("UPDATE copies SET status = $1 WHERE copy_id = $2", p2);

        tx.commit();
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void Service::checkin(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: returning <copy_id> <user_id>\n";
        return;
    }

    // Extract copy id and user id from args
    int copy_id = std::stoi(args[0]);
    int user_id = std::stoi(args[1]);
    std::string status = args[2];

    try {
        pqxx::work tx(conn_);

        // Update the borrow table with return date
        pqxx::params p;
        p.append(copy_id);
        p.append(user_id);

        tx.exec("UPDATE borrow SET return_date = NOW() Where copy_id = $1 AND user_id = $2 AND return_date IS NULL", p);

        // Update the copies table to change status of the copy from "available" to "checked-out"
        pqxx::params p2;
        p2.append(status);
        p2.append(copy_id);

        tx.exec("UPDATE copies SET status = $1 WHERE copy_id = $2", p2);

        tx.commit();
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void Service::view_borrow(const std::vector<std::string> &args) {
    if (!args.empty()) {
        std::cout << "Invalid command. This command does not expect any arguments.\n";
        return;
    }

    try {
        pqxx::read_transaction tx(conn_);

        pqxx::result r = tx.exec("SELECT users.user_id, first_name, last_name, borrow_id, books.isbn, title, copies.copy_id, status, borrow_date FROM books INNER JOIN copies ON books.isbn = copies.isbn INNER JOIN borrow ON copies.copy_id = borrow.copy_id INNER JOIN users ON borrow.user_id = users.user_id WHERE return_date IS NULL");

        // If result is empty, that means no active borrowing records exist
        if (r.empty()) {
            std::cout << "No active borrowing records exist.\n";
            return;
        } else {
            // Print header
            std::cout << std::left
                << std::setw(10) << "User ID"
                << std::setw(15) << "First Name"
                << std::setw(15) << "Last Name"
                << std::setw(15) << "Borrow ID"
                << std::setw(15) << "ISBN"
                << std::setw(25) << "Title"
                << std::setw(10) << "Copy ID"
                << std::setw(15) << "Status"
                << std::setw(30) << "Borrow Date"
                << "\n";
            std::cout << std::string(115, '-') << "\n";

            // Print content
            for (auto row : r) {
                std::cout << std::left
                    << std::setw(10) << row["user_id"].as<std::string>()
                    << std::setw(15) << row["first_name"].as<std::string>()
                    << std::setw(15) << row["last_name"].as<std::string>()
                    << std::setw(15) << row["borrow_id"].as<std::string>()
                    << std::setw(15) << row["isbn"].as<std::string>()
                    << std::setw(25) << row["title"].as<std::string>()
                    << std::setw(10) << row["copy_id"].as<std::string>()
                    << std::setw(15) << row["status"].as<std::string>()
                    << std::setw(30) << row["borrow_date"].as<std::string>()
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

void Service::view_all(const std::vector<std::string> &args) {
    // Validate inputs
    if (!args.empty()) {
        std::cout << "Invalid command. This command does not expect any arguments.\n";
        return;
    }

    try {
        pqxx::read_transaction tx(conn_);

        pqxx::result r = tx.exec("SELECT borrow_id, user_id, books.isbn, title, copies.copy_id, status, borrow_date, return_date FROM books INNER JOIN copies ON books.isbn = copies.isbn INNER JOIN borrow ON copies.copy_id = borrow.copy_id");

        // If result is empty, that means no active borrowing records exist
        if (r.empty()) {
            std::cout << "No borrowing records exist.\n";
            return;
        } else {
            // Print header
            std::cout << std::left
                << std::setw(15) << "Borrow ID"
                << std::setw(10) << "User ID"
                << std::setw(15) << "ISBN"
                << std::setw(25) << "Title"
                << std::setw(10) << "Copy ID"
                << std::setw(15) << "Status"
                << std::setw(30) << "Borrow Date"
                << std::setw(30) << "Return Date"
                << "\n";
            std::cout << std::string(130, '-') << "\n";

            // Print content
            for (auto row : r) {
                // Check for return date
                std::string return_date_str = row["return_date"].is_null() ? "NULL" : row["return_date"].as<std::string>();

                std::cout << std::left
                    << std::setw(15) << row["borrow_id"].as<std::string>()
                    << std::setw(10) << row["user_id"].as<std::string>()
                    << std::setw(15) << row["isbn"].as<std::string>()
                    << std::setw(25) << row["title"].as<std::string>()
                    << std::setw(10) << row["copy_id"].as<std::string>()
                    << std::setw(15) << row["status"].as<std::string>()
                    << std::setw(30) << row["borrow_date"].as<std::string>()
                    << std::setw(30) << return_date_str
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
