
# add all source files in the current source folder as sources
file(GLOB STACK_TEST_SOURCES "*.cpp")

add_executable(stack_test ${STACK_TEST_SOURCES})
target_link_libraries(stack_test testing_utils gtest gtest_main)

add_valgrind_gtests(stack_test)
