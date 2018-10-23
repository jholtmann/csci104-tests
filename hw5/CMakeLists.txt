cmake_minimum_required(VERSION 3.1)
project(HW5)
set(CMAKE_CXX_STANDARD 11)

### GTest ###
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(. tests)

# Feel free to uncomment this if you want to use cmake for compiling your programs
#add_executable(Cave
#        cave.cpp)

#add_executable(Functor
#        functor.cpp
#        functor.h)

add_executable(Fatalist-Test
        tests/fatalist_test.cpp)
add_test(Fatalist-Test Fatalist-Test)
target_link_libraries(Fatalist-Test gtest gtest_main)


add_executable(Functor-Test
        tests/functor_test.cpp)
add_test(Functor-Test Functor-Test)
target_link_libraries(Functor-Test gtest gtest_main)

add_executable(Merge-Test
	tests/utils/runtime_evaluator.cpp
        tests/merge_test.cpp)
add_test(Merge-Test Merge-Test)
target_link_libraries(Merge-Test gtest gtest_main)

add_executable(Cave-Test
        tests/cave_test.cpp)
add_test(Cave-Test Cave-Test)
target_link_libraries(Cave-Test gtest gtest_main)

