#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../inc/book.hpp"
#include "../inc/linked_list.hpp"

// Test case: adding to linked list/delete from linked list
TEST_CASE("Linked list operations", "[linked_list]") {
    Book algo(1, "Analysis of Algorithms", "Unknown", "Computer Science");
    Linked_List* list = new Linked_List();

    SECTION("Add node to linked list") {
        list->add_node(algo);
        REQUIRE(list->search_book(1, "Analysis of Algorithms") == true);
    }

    SECTION("Delete node from linked list") {
        list->add_node(algo);
        list->delete_node(1);
        REQUIRE(list->search_book(1, "Analysis of Algorithms") == false);
    }

    delete list;
}

