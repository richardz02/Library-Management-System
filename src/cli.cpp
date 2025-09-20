#include <string>
#include <vector>
#include "../inc/cli.hpp"
#include "../inc/library.hpp"
#include "../inc/user_management.hpp"

// CLI constructor
CLI::CLI(pqxx::connection& conn) : library(conn), user_management(conn) {
    // Book Operations
    dispatch_table["add-book"] = [&](const std::vector<std::string>& args){ library.add_book(args); };
    dispatch_table["search-book"] = [&](const std::vector<std::string>& args){ library.search_by_isbn(args); };
    dispatch_table["delete-book"] = [&](const std::vector<std::string> & args){ library.delete_book(args); };
    dispatch_table["list-books"] = [&](const std::vector<std::string>& args){ library.list_all_books(args); };

    // Copy Operations
    dispatch_table["insert-copy"] = [&](const std::vector<std::string>& args){ library.insert_copy(args); };
    dispatch_table["update-copy"] = [&](const std::vector<std::string>& args){ library.update_copy(args); };
    dispatch_table["remove-copy"] = [&](const std::vector<std::string>& args){ library.remove_copy(args); };
    dispatch_table["list-copies"] = [&](const std::vector<std::string>& args){ library.list_all_copies(args); };

    // User Operations
    dispatch_table["add-user"] = [&](const std::vector<std::string>& args){ user_management.add_user(args); };
    dispatch_table["search-user"] = [&](const std::vector<std::string>& args){ user_management.search_user(args); };
    dispatch_table["delete-user"] = [&](const std::vector<std::string>& args){ user_management.delete_user(args); };
    dispatch_table["list-users"] = [&](const std::vector<std::string>& args){ user_management.list_users(args); };

    // Other
    dispatch_table["help"] = [&](const std::vector<std::string>& args){ library.help(args); };
    dispatch_table["exit"] = [&](const std::vector<std::string>& args){ library.exit_program(args); };
}

void CLI::run() {
    while (1) {
        std::cout << "Library> " << std::flush;

        std::string usr_command; // String to store user command
        std::getline(std::cin, usr_command); // Read user command from standard input

        // Split the user command string into tokens for further parsing
        std::string current_token;
        std::vector<std::string> tokens;
        bool inside_quotes = false;

        // Parse user command
        for (char c : usr_command) {
            // Every time we encounter quotes, we flip the boolean variable inside_quotes to indicate
            // whether we are entering a quote or leaving it
            if (c == '"') {
                inside_quotes = !inside_quotes;
            }
            // If we encounter a white space and we are not inside a quote, and if the current token is not empty
            // add to tokens vector
            else if (c == ' ' && inside_quotes == false) {
                if (!current_token.empty()) {
                    tokens.push_back(current_token);
                    current_token.clear();
                }
            }
            // For everything else, we simply add to current token
            else {
                current_token.push_back(c);
            }
        }

        // At the end, if current token is not empty, push to tokens vector
        if (!current_token.empty())
            tokens.push_back(current_token);

        // Extract the command from the first token
        std::string command = tokens[0];

        // Rest of the tokens in the vector are arguments
        tokens.erase(tokens.begin());

        auto it = dispatch_table.find(command);
        if (it != dispatch_table.end()) {
            it->second(tokens);
        } else {
            std::cout << "Unknow command. Enter \"help\" to see the help menu.\n";
            continue;
        }
    }
}
