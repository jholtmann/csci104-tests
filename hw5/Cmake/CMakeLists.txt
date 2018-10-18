cmake_minimum_required(VERSION 3.1)
project(HW5)
set(CMAKE_CXX_STANDARD 11)

### GTest ###
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(.)

# Feel free to uncomment this if you want to use cmake for compiling your programs
#add_executable(Cave
#        cave.cpp)

#add_executable(Functor
#        functor.cpp
#        functor.h)

add_executable(Fatalist-Test
        Fatalist-Test.cpp)
add_test(Fatalist-Test Fatalist-Test)
target_link_libraries(Fatalist-Test gtest gtest_main)
