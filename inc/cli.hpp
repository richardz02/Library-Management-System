#include "library.hpp"

#ifndef CLI_H_
#define CLI_H_

class CLI {
    Library library;
public:
        CLI(const std::string& connection_info) : library(connection_info) {}
        void run();
};


#endif // CLI_H_
