#include "../inc/library.hpp"

// Adding a book to the library
void Library::add_book(std::string isbn, std::string title, std::string author, std::string publication_date) {
    Book book{isbn, title, author, publication_date};

    map[isbn] = title;
}

// Deleting a book from the library
void Library::delete_book(std::string isbn) {
    if (!map.count(isbn)) {
        std::cout << "Book does not exist." << std::endl;
        return;
    }

    map.erase(isbn);
}

// Search book by isbn, return book title
std::optional<std::string> Library::search_by_isbn(std::string isbn) {
    if (!map.count(isbn)) {
        std::cout << "Book does not exist." << std::endl;
        return std::nullopt;
    }

    std::string book_title = map[isbn];

    return book_title;
}
