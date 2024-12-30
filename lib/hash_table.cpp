#include "../inc/hash_table.hpp"
#include <stdexcept>
#include <stdio.h>

// Constructor
// Set size of array and initialize Linked_List pointer array to null pointers
Hash_Table::Hash_Table() {
    this->numBooks = 0;
    this->array = new Linked_List*[array_size]();
}

// Destructor
// Delete Linked_List pointer array and free up memory
Hash_Table::~Hash_Table() {
    delete[] array;
}

// Return the table size
int Hash_Table::get_size() {
    return array_size;
}

// Return the number of books stored in the hash table
int Hash_Table::get_numBooks() {
    return numBooks;
}

// Hash function
int Hash_Table::hash_function(int book_id) {
    int bucket = book_id % array_size;
    return bucket;
}

// Calculate the load factor
float Hash_Table::calculate_load_factor() {
    float load_factor = (float)numBooks / (float)array_size;
    return load_factor;
}

// Based on the load factor, decide whether resizing array is necessary
void Hash_Table::resize_array() {
    int old_size = array_size;
    // Set new array size to double original array size
    array_size = array_size * 2;

    // Allocate memory for new array
    Linked_List** new_array = new Linked_List*[array_size]();

    // Rehash entries
    for (int i = 0; i < old_size; i++) {
        // If bucket is not nullptr, traverse linked list
        if (array[i] != nullptr) {
            Node* current = array[i]->head;
            while (current != nullptr) {
                int new_index = hash_function(current->book.get_id());
                if (new_array[new_index] == nullptr)
                    new_array[new_index] = new Linked_List();
                new_array[new_index]->add_node(current->book);
                current = current->next;
            }
        }
        // Delete the linked list in the bucket
        delete array[i];
    }

    // Deallocate memory for old array
    delete[] array;

    // Set array to new array
    array = new_array;
}

// Add a book to the hash table
void Hash_Table::add_book(Book book) {
    // Get the bucket index by applying the hash function
    int bucket_index = hash_function(book.get_id());

    // Check if there is a linked list initialized at the bucket
    // If bucket points to a nullptr, create new linked list
    if (array[bucket_index] == nullptr) {
        array[bucket_index] = new Linked_List();
    }

    // Append book to the linked list
    array[bucket_index]->add_node(book);

    // Increment number of books by 1
    numBooks++;

    // Calculate load factor
    float load_factor = calculate_load_factor();

    // If load factor exceeds load factor threshold
    // Resize array
    if (load_factor >= load_threshold) {
        std::cout << "Resizing array and rehashing book entries" << std::endl;
        resize_array();
        std::cout << "New array size: " << array_size << std::endl;
    }
}

// Return the book node
std::optional<Book> Hash_Table::search_by_id(int book_id) {
    // Get the bucket index of the book
    int bucket_index = hash_function(book_id);

    // If the bucket index is nullptr, return nullptr
    if (array[bucket_index] == nullptr)
        return std::nullopt;

    Node* current = array[bucket_index]->head;
    while (current != nullptr) {
        if (current->book.get_id() == book_id) {
            return current->book;
            break;
        }
    }

    return std::nullopt;
}

std::vector<Book> Hash_Table::search_by_title(std::string book_title) {
    std::vector<Book> books;

    for (int i = 0; i < array_size; i++) {
        if (array[i] != nullptr) {
            Node* current = array[i]->head;
            while (current != nullptr) {
                if (current->book.get_title() == book_title) {
                    books.push_back(current->book);
                }
                current = current->next;
            }
        }
    }

    return books;
}

// Delete book from hash table
void Hash_Table::delete_book(int book_id) {
    // Get the bucket index for the book
    int bucket_index = hash_function(book_id);

    // If the bucket index has a nullptr, print error message
    if (array[bucket_index] == nullptr)
        std::cout << "Book does not exist.";

    array[bucket_index]->delete_node(book_id);

    numBooks--;
}

void Hash_Table::display() {
    for (int i = 0; i < array_size; i++) {
        if (array[i] != nullptr) {
            std::cout << "Bucket " << i << ": " << std::endl;
            array[i]->display_node();
            std::cout << "----------------------------------" << std::endl;
        }
    }
}

std::vector<Book> Hash_Table::return_booklist() {
    std::vector<Book> books;

    for (int i = 0; i < array_size; i++) {
        if (array[i] != nullptr) {
            Node* current = array[i]->head;
            while (current != nullptr) {
                books.push_back(current->book);
                current = current->next;
            }
        }
    }

    return books;
}
