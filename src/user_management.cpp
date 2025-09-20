#include <exception>
#include "../inc/user_management.hpp"

void User_Management::add_user(const std::vector<std::string> &args) {
    // Validate inputs
    if (args.size() != 3) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: add-user <email> <first name> <last name>\n";
        return;
    }

    // Extract arguments from args array
    std::string first_name = args[0];
    std::string last_name = args[1];
    std::string email = args[2];

    try {
        // Create a transaction to insert new user information into the database
        pqxx::work tx(conn_);

        pqxx::params p;
        p.append(first_name);
        p.append(last_name);
        p.append(email);

        tx.exec("INSERT INTO users (first_name, last_name, email) VALUES ($1, $2, $3)", p);
        tx.commit();
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void User_Management::search_user(const std::vector<std::string> &args) {
    // Validate user input
    if (args.size() != 1) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: search-user <user id>\n";
        return;
    }

    int user_id = std::stoi(args[0]);

    try {
        pqxx::read_transaction tx(conn_);

        pqxx::params p;
        p.append(user_id);

        pqxx::result r = tx.exec("SELECT first_name, last_name, email FROM users WHERE user_id = $1", p);

        // If the result came back empty, return message that user does not exist
        if (r.empty()) {
            std::cout << "User with user_id: " << user_id << " does not exist.\n";
            return;
        } else {
            auto row = r[0];

            std::cout << "First name: " << row["first_name"].as<std::string>() << "\n";
            std::cout << "Last name: " << row["last_name"].as<std::string>() << "\n";
            std::cout << "Email: " << row["email"].as<std::string>() << "\n";
        }
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void User_Management::delete_user(const std::vector<std::string> &args) {
    // Validate inputs
    if (args.size() != 1) {
        std::cout << "Invalid command.\n";
        std::cout << "Usage: delete-user <user id>\n";
        return;
    }

    int user_id = std::stoi(args[0]);

    try {
        pqxx::work tx(conn_);

        pqxx::params p;
        p.append(user_id);

        tx.exec("DELETE from users WHERE user_id = $1", p);
        tx.commit();
    } catch (const pqxx::sql_error &e) {
        // Catch SQL execution errors, and print out query and caused the error
        std::cerr << "SQL error: " << e.what() << "\nQuerry: " << e.query() << std::endl;
    } catch (const std::exception &e) {
        // Catch any unexpected errors
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

void User_Management::list_users(const std::vector<std::string> &args) {
    // Validate inputs
    if (!args.empty()) {
        std::cout << "Invalid command. This command does not expect any arguments.\n";
        return;
    }

    try {
        pqxx::work tx(conn_);

        pqxx::result r = tx.exec("SELECT * FROM users");

        // If result is empty, that means no users exist in the database yet
        if (r.empty()) {
            std::cout << "No users exist in the database.\n";
            return;
        } else {
            // Print header
            std::cout << std::left
                << std::setw(10) << "User ID"
                << std::setw(15) << "First Name"
                << std::setw(15) << "Last Name"
                << std::setw(35) << "Email"
                << "\n";
            std::cout << std::string(65, '-') << "\n";

            // Iterate through all the records returned and display them
            for (auto row : r) {
                std::cout << std::left
                    << std::setw(10) << row["user_id"].as<std::string>()
                    << std::setw(15) << row["first_name"].as<std::string>()
                    << std::setw(15) << row["last_name"].as<std::string>()
                    << std::setw(35) << row["email"].as<std::string>()
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
