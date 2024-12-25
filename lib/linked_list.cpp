#include "../inc/linked_list.hpp"

// Constructor
// Set head of linked list to null pointer
Linked_List::Linked_List() : head(nullptr) {};

// Destructor
// Delete nodes from linked list and free up memory
Linked_List::~Linked_List() {
        while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
        }
        head = nullptr;
}

void Linked_List::add_node(Book book) {
        // Creating a new node
        Node *new_node = new Node(book);

        // Edge case: if head is null, insert new node at head
        if (head == nullptr) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                    current = current->next;
            }
            current->next = new_node;
        }
}

// Three scenarios for deleting node from linked list
// 1. Delete head node
// 2. Delete node in the middle
// 3. Delete last node
void Linked_List::delete_node(int book_id) {
        // If linked list is empty, return immediately
        if (head == nullptr) {
                return;
        }

        // Find the node to be deleted
        Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr) {
                if (current->book.get_id() == book_id) {
                        break; // Found the node to delete
                } else {
                        prev = current;
                        current = current->next;
                }
        }

        // If the node is not found, return
        if (current == nullptr)
                return;

        // Delete at beginning
        if (current == head) {
                head = head->next;
        }
        // Delete in middle or the end
        else {
                prev->next = current->next;
        }

        // Delete node and free memory
        delete current;
}

// Searches for a book in the linked list given book id and title
bool Linked_List::search_book(int book_id, std::string book_title) {
        Node* current = head;

        // Loop through the linked list to search for book
        // If book is found, return pointer to node containing book
        while (current != nullptr) {
                if (current->book.get_id() == book_id && current->book.get_title() == book_title)
                        return true;
                else
                        current = current->next;
        }

        // If corresponding book is found, return null pointer
        return false;
}

// Traverses the linked list and display node information
void Linked_List::display_node() {
        Node* current = head;

        while (current != nullptr) {
                current->book.display_book_info();
                current = current->next;
        }
}

// Returns book details given book id
Node* Linked_List::get_book(int book_id) {
        Node* current = head;

        // Loop through the linked list to search for book
        // If book is found, return pointer to node containing book
        while (current != nullptr) {
                if (current->book.get_id() == book_id)
                        return current;
                else
                        current = current->next;
        }

        // If corresponding book is found, return null pointer
        return nullptr;
}
