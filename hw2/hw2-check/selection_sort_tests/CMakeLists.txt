# add all source files in the current source folder as sources
file(GLOB SELECTION_SORT_TEST_SOURCES "*.cpp")

add_executable(selection_sort_test ${SELECTION_SORT_TEST_SOURCES})
target_link_libraries(selection_sort_test testing_utils gtest gtest_main)

add_valgrind_gtests(selection_sort_test)