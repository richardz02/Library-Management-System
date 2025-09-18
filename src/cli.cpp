#include <string>
#include <vector>
#include "../inc/cli.hpp"
#include "../inc/library.hpp"

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

        // If user enters "help", display help menu
        if (tokens[0] == "help") {
            // help menu for book operations
            std::cout << "Book Operations\n";
            std::cout << "1. Add a book: add-book <ISBN> <Title> <Author> <Publication Date>\n";
            std::cout << "2. Search by ISBN: search-book <ISBN>\n";
            std::cout << "3. Remove a book: remove-book <ISBN>\n";
            std::cout << "4. Display all books: display-books\n";
            std::cout << "5. Exit program: exit\n";
            std::cout << "\n";

            // help menu for managing copies of books
            std::cout << "Copy Operations\n";
            std::cout << "1. Insert copies: insert-copy <ISBN> (Default status: available)\n";
            std::cout << "3. Update copy: update-copy <Copy ID> <New Status>\n";
            std::cout << "4. Remove copy: remove-copy <Copy ID>\n";
            std::cout << "5. Display all copies: display-copies\n";
        }
        // If user enters "exit", exit program
        else if (tokens[0] == "exit") {
            exit(0);
        }
        else if (tokens[0] == "add-book") {
            // Check if the command has the correct size
            if (tokens.size() != 5) {
                std::cout << "Invalid command." << std::endl;
                continue;
            }

            // Parse the add-book command to get the parameters
            std::string isbn = tokens[1];
            std::string title = tokens[2];
            std::string author = tokens[3];
            std::string publication_date = tokens[4];

            // Creating a Book object
            Book book{isbn, title, author, publication_date};

            // Pass in the book object to the library function call add_book
            library.add_book(book);
        }
        else if (tokens[0] == "search-book") {
            if (tokens.size() != 2) {
                std::cout << "Invalid command." << std::endl;
                continue;
            }

            std::string isbn = tokens[1];
            library.search_by_isbn(isbn);
        }
        else if (tokens[0] == "remove-book") {
            if (tokens.size() != 2) {
                std::cout << "Invalid command." << std::endl;
                continue;
            }

            std::string isbn = tokens[1];
            library.delete_book(isbn);
        }
        else if (tokens[0] == "display-books") {
            if (tokens.size() != 1) {
                std::cout << "Invalid command.\n";
                continue;
            }

            library.display_all_books();
        }
        else if (tokens[0] == "insert-copy") {
            if (tokens.size() != 3) {
                std::cout << "Invalid command.\n";
                continue;
            }

            std::string isbn = tokens[1];
            int num_copies = std::stoi(tokens[2]);

            library.insert_copy(isbn, num_copies);
        }
        else if (tokens[0] == "update-copy") {
            if (tokens.size() != 3) {
                std::cout << "Invalid command.\n";
                continue;
            }

            int copy_id = std::stoi(tokens[1]);
            std::string new_status = tokens[2];

            // Check status
            // Status can only be: available, checked-out, damaged, or lost
            // NOTE: Might want to create a class/struct in the future for better maintenance
            if (new_status != "available" && new_status != "checked-out" && new_status != "damaged" && new_status != "lost") {
                std::cout << "Status must be one of the following: available, checked-out, damaged, lost.\n";
                continue;
            }

            library.update_copy(copy_id, new_status);
        }
        else if (tokens[0] == "remove-copy") {
            if (tokens.size() != 2) {
                std::cout << "Invalid command.\n";
                continue;
            }

            int copy_id = std::stoi(tokens[1]);
            library.remove_copy(copy_id);
        }
        else if (tokens[0] == "display-copies") {
            if (tokens.size() != 1) {
                std::cout << "Invalid command.\n";
                continue;
            }

            library.display_all_copies();
        }
        else {
            std::cout << "Invalid command. Type \"help\" to see the help menu." << std::endl;
        }
    }
}
