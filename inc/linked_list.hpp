#include "book.hpp"

#ifndef LINKED_LIST
#define LINKED_LIST

class Node {
    public:
        Book book;
        Node* next;
        Node(Book book) : book(book), next(nullptr) {}
};

class Linked_List {
    public:
        Node* head;

        // Define constructor and destructor
        Linked_List();
        ~Linked_List();

        // Adding a node representing book to the linked list
        void add_node(Book book);

        // Delete a node representing a book from the linked list
        void delete_node(int book_id);

        // Search for a particular book
        bool search_book(int book_id, std::string book_title);

        // Display information about every node in the linked list
        void display_node();

        Node* get_book(int book_id);
};

#endif
