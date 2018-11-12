# add all source files in the current source folder as sources
file(GLOB AVL_TEST_SOURCES "*.cpp")

add_executable(avl_test ${AVL_TEST_SOURCES})
target_link_libraries(avl_test testing_utils gtest gtest_main)

add_valgrind_gtests(avl_test)
