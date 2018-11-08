# add all source files in the current source folder as sources
file(GLOB BST_TEST_SOURCES "*.cpp")

add_executable(bst_test ${BST_TEST_SOURCES})
target_link_libraries(bst_test testing_utils gtest gtest_main)

add_valgrind_gtests(bst_test)
