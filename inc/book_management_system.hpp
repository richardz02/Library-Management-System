#include "../inc/sorting.hpp"
#include "../inc/hash_table.hpp"

#ifndef BOOK_MANAGEMENT_SYSTEM_H_
#define BOOK_MANAGEMENT_SYSTEM_H_

class Book_Management_System {
    Hash_Table ht;

    public:
        Book_Management_System(int ht_size);

        // Add book to library
        void add_book(Book book);

        // Delete book from library
        void delete_book(int book_id);

        // Loop up if a book exists, user can search by id or title
        std::vector<Book> lookup_book(std::string input);
};


#endif // BOOK_MANAGEMENT_SYSTEM_H_
