# Library Management System
This is a command-line interface application that mimics a real world application as close as possible. Instead of using custom data structures like I did before, I am rewriting the entire codebase to utilize data structures in the C++ STL and integrating with a database (PostGreSQL).

Some functionalities of the library management system is as follows:
- Add a book to the library
- Search for a book in the library
- Delete a book from the library
- Display all the books the library has stored
- Track user interactions with the library, including borrowing, returning, etc

## How to run

### Set up
- Make sure you have PostgreSQL set up locally in your system
- Create a .pgpass file to store your credentials
- Specify the connection information in the program and pass it in the cli() object in main.cpp

### Commands
- Create a ```build``` directory from the project root directory
- Go into the ```build``` directory and enter command ```cmake ..```
- enter the ```make``` command after cmake runs successfully
- To run the program, enter ```./library-management```
