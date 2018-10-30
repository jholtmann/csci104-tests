
# add all source files in the current source folder as sources
file(GLOB CIRCULAR_LIST_TEST_SOURCES "*.cpp")

add_executable(circular_list_test ${CIRCULAR_LIST_TEST_SOURCES})
target_link_libraries(circular_list_test testing_utils gtest gtest_main)

add_valgrind_gtests(circular_list_test)