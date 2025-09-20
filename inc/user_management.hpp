#include <pqxx/pqxx>
#include <vector>
#include "user.hpp"

#ifndef USER_MANAGEMENT_H_
#define USER_MANAGEMENT_H_

class User_Management {
private:
        pqxx::connection& conn_;
public:
        User_Management(pqxx::connection& conn) : conn_(conn) {}

        /**
         * @brief Adds a new user to the database
         *
         * This function takes in an email, and user's full name, and adds a new user to the database
         *
         * args is expected to have:
         * args[0]: user first name
         * args[1]: user last name
         * args[2]: user email
         */
        void add_user(const std::vector<std::string>& args);

        /**
         * @brief Searches for a user by user id
         *
         * This function takes in an user id, and returns the relevant information of that user
         *
         * args is expected to have:
         * args[0]: user id
         */
        void search_user(const std::vector<std::string>& args);

        /**
         * @brief Deletes a user from the database by user id
         *
         * This function takes in an user id, then deletes that user by user id
         *
         * args is expected to have:
         * args[0]: user id
         */
        void delete_user(const std::vector<std::string>& args);

        /**
         * @brief Displays all users in the database
         *
         * This function lists all users registered in the database
         */
         void list_users(const std::vector<std::string>& args);
};

#endif // USER_MANAGEMENT_H_
