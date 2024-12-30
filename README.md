# Library-Management-System
This project mimics the library management system by allowing users to search and borrow books. 

## Hashtable for storing books
- The implementation of hash table will be a pointer array of linked lists (separate chaining).
- Each slot will store a bucket and each bucket can contain a linked list of key-value pairs
- A hash function will be implemented
- Hash table should have a load factor, and if the load factor exceeds the threshold, double array size to reduce collision

## Sorting
Library system will allow the user to choose to display the books in some kind of order.
- Use quicksort for displaying books in ascending order by book id
