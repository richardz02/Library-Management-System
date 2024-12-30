#include <iostream>
#include "../inc/book_management_system.hpp"

Book_Management_System::Book_Management_System() : ht() {}


void Book_Management_System::add_book(Book book) {
    ht.add_book(book);
}

void Book_Management_System::delete_book(int book_id) {
    ht.delete_book(book_id);
}

// This is a helper function for the lookup function
// Determines if a string is number
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

// Returns a specific book if user enters book id
// Returns a list of books if user enters book title
std::vector<Book> Book_Management_System::lookup_book(std::string input) {
    std::vector<Book> result;

    // If user enters book id, search by id
    // else, search by book title
    if (is_number(input)) {
        int book_id = std::stoi(input);
        std::optional<Book> book_optional = ht.search_by_id(book_id);

        if (book_optional.has_value()) {
            Book book = book_optional.value();
            result.push_back(book);
        }
    } else {
        result = ht.search_by_title(input);
    }

    return result;
}

void Book_Management_System::display_all_ascending() {
    std::vector<Book> books = ht.return_booklist();

    // Quicksort to sort books in ascending order
    quick_sort(books, 0, books.size() - 1);

    for (Book book : books) {
        std::cout << "Book id: " << book.get_id() << ", Title: " << book.get_title() << std::endl;
    }
}
