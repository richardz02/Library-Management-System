cmake_minimum_required(VERSION 3.28.3)

project(library_management)

# Specify include directories
include_directories(inc)

# Add main application executable
add_executable(
  ${PROJECT_NAME}
  lib/hash_table.cpp
  lib/linked_list.cpp
  exe/main.cpp
)

# Add a library target for shared functionality
add_library(
  library_management_lib
  lib/hash_table.cpp
  lib/linked_list.cpp
)
target_include_directories(library_management_lib PUBLIC inc)

# Find Catch2 for testing
find_package(Catch2 REQUIRED)

# Enable testing
enable_testing()

# Add test executables for individual components
add_executable(test_linked_list tests/test_linked_list.cpp)

# Link Catch2 and the shared library
target_link_libraries(test_linked_list PRIVATE Catch2::Catch2WithMain library_management_lib)

# Register tests with Ctests
include(Catch)
catch_discover_tests(test_linked_list)
