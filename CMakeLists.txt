# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

# Define project name
project(library-management)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SOURCE_FILES
  main.cpp
  src/cli.cpp
  src/library.cpp
  src/user_management.cpp
  src/service.cpp
)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE pqxx pq)
