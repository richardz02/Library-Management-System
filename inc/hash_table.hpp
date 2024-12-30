#include <optional>
#include <vector>
#include "linked_list.hpp"
#include "book.hpp"

#ifndef HASH_TABLE
#define HASH_TABLE

class Hash_Table {
    // To keep track of the number of books in the hash table
    int numBooks;

    // Array size
    int array_size = 10;

    // Dynamically allocate memory
    // A pointer to an array of pointers to Linked_List
    Linked_List** array;

    // Set a predefine load factor threshold
    float load_threshold = 0.75;

    // Hash function: book_id % size of array
    int hash_function(int book_id);

    // Resize array
    void resize_array();

    // Calculate load factor: number of elements / number of buckets
    float calculate_load_factor();

    public:
        // Constructor and destructor
        Hash_Table();
        ~Hash_Table();

        // Get the size of the hash table
        int get_size();

        // Get number of books stored in the hash table
        int get_numBooks();

        // Add book to the hash table
        void add_book(Book book);

        // If user is searching for book id, returns the book user is looking for
        std::optional<Book> search_by_id(int book_id);

        // If user is searching for book title, returns a list of books with same title
        std::vector<Book> search_by_title(std::string book_title);

        // Delete book from the hash table
        void delete_book(int book_id);

        // Displays every book stored in the hash table
        void display();

        // Returns a vector of type class Book containing all the books
        std::vector<Book> return_booklist();
};

#endif // HASH_TABLE
