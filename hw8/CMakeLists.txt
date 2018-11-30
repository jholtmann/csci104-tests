cmake_minimum_required(VERSION 3.1)
add_compile_options(-Wall -std=c++11)
set(CMAKE_C_STANDARD 11)
project(Scrabble)

### GTest ###
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Trie-Test
        trie-tests/trie-test.cpp
	# Change these depending on where you put them
        src/Trie.cpp
        lib/Trie.h
        )
add_test(Trie-Test Trie-Test)
target_link_libraries(Trie-Test gtest gtest_main)
