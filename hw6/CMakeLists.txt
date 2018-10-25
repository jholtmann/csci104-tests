cmake_minimum_required(VERSION 3.1)
project(HW5)
set(CMAKE_CXX_STANDARD 11)

### GTest ###
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(.)

add_executable(MinHeap-Test
        tests/minheap_test.cpp
        )
add_test(MinHeap-Test MinHeap-Test)
target_link_libraries(MinHeap-Test gtest gtest_main)

add_executable(Search-Test
        tests/search_test.cpp
        )
add_test(Search-Test Search-Test)
target_link_libraries(Search-Test gtest gtest_main)

add_executable(Color-Test
        tests/color_test.cpp
        )
add_test(Color-Test Color-Test)
target_link_libraries(Color-Test gtest gtest_main)