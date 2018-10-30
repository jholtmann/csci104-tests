
# make sure that the tests have a directory to put their output files
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testFiles)

# add all source files in the current source folder as sources
file(GLOB DDG_TEST_SOURCES "*.cpp")

add_executable(duck_duck_goose_test ${DDG_TEST_SOURCES})
add_dependencies(duck_duck_goose_test duck_duck_goose)
target_link_libraries(duck_duck_goose_test testing_utils hw2_user_code gtest gtest_main)

add_valgrind_gtests(duck_duck_goose_test)