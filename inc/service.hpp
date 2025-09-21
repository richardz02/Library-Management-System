#include <pqxx/pqxx>

#ifndef SERVICE_H_
#define SERVICE_H_

class Service {
private:
        pqxx::connection& conn_;

public:
        Service(pqxx::connection& conn) : conn_(conn){}

        /**
         * @brief User checks out a copy of a book
         *
         * This function allows the user to check out a copy of a book, and updates the status of the book
         *
         * args is expected to have:
         * args[0]: user id
         * args[1]: copy id
         */
        void checkout(const std::vector<std::string>& args);

        /**
         * @brief User returns the book
         *
         * This function allows the user to return a copy of a book, and updates the status of the book
         *
         * args is expected to have:
         * args[0]: user id
         * args[1]: copy id
         * args[2]: new status
         */
        void checkin(const std::vector<std::string>& args);

        /**
         * @brief Lists all active borrowing records (those who haven't returned)
         *
         * This function displays a detailed view of all active borrowing records
         * This function does not expect any arguments
         */
        void view_borrow(const std::vector<std::string>& args);

        /**
         * @brief Lists all borrowing records, regardless of whether they are returned or not
         *
         * This function displays all of the existing records in the borrow table
         * This function does not expect any arguments
         */
         void view_all(const std::vector<std::string>& args);
};


#endif // SERVICE_H_
