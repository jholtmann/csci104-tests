# add all source files in the current source folder as sources
file(GLOB HEAP_TEST_SOURCES "*.cpp")

add_executable(heap_test ${HEAP_TEST_SOURCES})
target_link_libraries(heap_test testing_utils gtest gtest_main)

add_valgrind_gtests(heap_test)
