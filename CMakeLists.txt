cmake_minimum_required(VERSION 3.10)
project(LibrarySystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add sqlite3 source file
add_library(sqlite3 STATIC sql/sqlite3.c)
target_include_directories(sqlite3 PUBLIC sql)

# List your project source files
set(SOURCES
    Main.cpp
    Librarian.cpp
    User.cpp
)

# Create the executable
add_executable(LIBMAS ${SOURCES})

# Link sqlite3 to your project
target_link_libraries(LIBMAS PRIVATE sqlite3)
