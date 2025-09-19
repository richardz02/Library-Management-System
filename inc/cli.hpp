#include <unordered_map>
#include "library.hpp"

#ifndef CLI_H_
#define CLI_H_

class CLI {
private:
    Library library;
    std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> dispatch_table;

public:
        CLI(const std::string& connection_info);
        void run();
};


#endif // CLI_H_
