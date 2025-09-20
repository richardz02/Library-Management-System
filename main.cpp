#include <exception>
#include <iostream>
#include <optional>
#include <vector>
#include "inc/library.hpp"
#include "inc/cli.hpp"

#include <pqxx/pqxx>

int main() {
    const std::string connection_info = "dbname=library_db user=bigrich host=localhost port=5432";
    pqxx::connection conn(connection_info);
    CLI cli(conn);
    cli.run();
}
