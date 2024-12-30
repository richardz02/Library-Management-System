#include "../inc/cli.hpp"
#include <string>

void CLI::display_menu() {
    std::cout << "Book Management System" << std::endl;
    std::cout << "1. Add a book" << std::endl;
    std::cout << "2. Delete a book" << std::endl;
    std::cout << "3. Look up a book" << std::endl;
    std::cout << "4. Quit" << std::endl;
}

void CLI::add_book() {
    std::string title, author, genre;
    int id;

    // Prompt user to enter book id
    std::cout << "Enter book id: ";
    std::cin >> id;
    std::cin.ignore();

    // Prompt user to enter book title
    std::cout << "Enter book title: ";
    std::getline(std::cin, title);

    // Promp user to enter author
    std::cout << "Enter author name: ";
    std::getline(std::cin, author);

    // Promp user to enter genre
    std::cout << "Enter book genre: ";
    std::getline(std::cin, genre);

    bms.add_book(Book(id, title, author, genre));
    std::cout << "Book added successfully." << std::endl;
}

void CLI::delete_book() {
    int id;

    // Prompt user to enter book id to delete
    std::cout << "Enter the id of the book you want to delete: ";
    std::cin >> id;
    std::cin.ignore();

    bms.delete_book(id);
    std::cout << "Book deleted successfully." << std::endl;
}

void CLI::search_book() {
    std::vector<Book> books;
    std::string search_input;

    // Prompt user to input search
    std::cin.ignore();
    std::cout << "Enter book id or title to search: ";
    std::getline(std::cin, search_input);

    books = bms.lookup_book(search_input);

    if (!books.empty())
        std::cout << "Book found." << std::endl;
    else
        std::cout << "Book not found." << std::endl;
}

void CLI::run() {
    while (true) {
        display_menu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case (1):
                add_book();
                break;
            case (2):
                delete_book();
                break;
            case (3):
                search_book();
                break;
            case (4):
                std::cout << "Existing..." << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again" << std::endl;
        }
    }
}
