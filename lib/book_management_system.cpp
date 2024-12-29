#include <iostream>
#include "../inc/book_management_system.hpp"

Book_Management_System::Book_Management_System(int ht_size) : ht(ht_size) {}


void Book_Management_System::add_book(Book book) {
    ht.add_book(book);
}

void Book_Management_System::delete_book(int book_id) {
    ht.delete_book(book_id);
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

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
