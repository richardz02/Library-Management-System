#include <iostream>

#ifndef BOOK
#define BOOK

class Book {
    int book_id;
    std::string title;
    std::string author;
    // Add published date here
    std::string genre;

    public:
        Book(int id, std::string title, std::string author, std::string genre) :
            book_id(id), title(title), author(author), genre(genre) {}

        std::string get_title() {
            return this->title;
        }

        int get_id() {
            return this->book_id;
        }

        void display_book_info() {
            std::cout << "Book id: " << this->book_id << std::endl;
            std::cout << "Title: " << this->title << std::endl;
            std::cout << "Author: " << this->author << std::endl;
            std::cout << "Genre: " << this->genre << std::endl;
        }

        // Overload == operator to compare if two books are the same
        bool operator==(Book& book) {
            return (this->book_id == book.book_id && this->title == book.title);
        }
};


#endif // BOOK
