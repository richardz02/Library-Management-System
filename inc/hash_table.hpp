#include "linked_list.hpp"
#include "book.hpp"

#ifndef HASH_TABLE
#define HASH_TABLE

class Hash_Table {
    // To keep track of the number of books in the hash table
    int numBook;

    // Array size
    int array_size;

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
        Hash_Table(int size);
        ~Hash_Table();

        // Add book to the hash table
        void add_book(Book book);

        // Search book in hash table
        Node* search_book(int book_id);

        // Delete book from the hash table
        void delete_book(int book_id);

        // Displays every book stored in the hash table
        void display();
};

#endif // HASH_TABLE