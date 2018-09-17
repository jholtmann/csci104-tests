cmake_minimum_required(VERSION 3.1)
project(HW3-TEST C CXX)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_compile_options(-Wall -std=c++11)

set(CMAKE_C_STANDARD 11)

include_directories(. ../hw2)

add_executable(stack
        stackint.cpp
        stackint.h
        ../hw2/circular_list_int.cpp
        ../hw2/circular_list_int.h)

add_executable(parser
        parser.cpp
        parser.h
        stackint.cpp
        stackint.h
        ../hw2/circular_list_int.cpp
        ../hw2/circular_list_int.h)

add_executable(stack-test
        stackint.cpp
        stackint.h
        ../hw2/circular_list_int.cpp
        ../hw2/circular_list_int.h
        stack-test.cpp
)

target_link_libraries(stack-test gtest gtest_main)

add_executable(parser-test
        parser.cpp
        parser.h
        stackint.cpp
        stackint.h
        ../hw2/circular_list_int.cpp
        ../hw2/circular_list_int.h
        parser-test.cpp)

target_link_libraries(parser-test gtest gtest_main)

