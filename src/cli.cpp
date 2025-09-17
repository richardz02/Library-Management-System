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
            std::cout << "Help Menu: " << std::endl;
            std::cout << "1. Add a book: add-book <ISBN> <Title> <Author> <Publication Date>" << std::endl;
            std::cout << "2. Search by ISBN: search-book <ISBN>" << std::endl;
            std::cout << "3. Remove a book: remove-book <ISBN>" << std::endl;
            std::cout << "4. Display all books: display-all" << std::endl;
            std::cout << "5. Exit program: exit" << std::endl;
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
        else if (tokens[0] == "display-all") {
            if (tokens.size() != 1) {
                std::cout << "Invalid command." << std::endl;
                continue;
            }

            library.display_all();
        }
        else {
            std::cout << "Invalid command. Type \"help\" to see the help menu." << std::endl;
        }
    }
}
