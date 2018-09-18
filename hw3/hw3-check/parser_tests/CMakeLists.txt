
# add all source files in the current source folder as sources
file(GLOB STACK_TEST_SOURCES "*.cpp")

add_executable(parser_test ${STACK_TEST_SOURCES})
target_link_libraries(parser_test testing_utils gtest gtest_main)

add_valgrind_gtests(parser_test)
