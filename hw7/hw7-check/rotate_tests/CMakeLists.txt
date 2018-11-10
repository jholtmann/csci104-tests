# add all source files in the current source folder as sources
file(GLOB ROTATE_TEST_SOURCES "*.cpp")

add_executable(rotate_test ${ROTATE_TEST_SOURCES})
target_link_libraries(rotate_test testing_utils gtest gtest_main)

add_valgrind_gtests(rotate_test)
