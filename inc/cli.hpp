#include <unordered_map>
#include "library.hpp"
#include "user_management.hpp"
#include "service.hpp"

#ifndef CLI_H_
#define CLI_H_

class CLI {
private:
    Library library;
    User_Management user_management;
    Service service;
    std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> dispatch_table;

public:
        CLI(pqxx::connection& conn);
        void run();
};


#endif // CLI_H_
