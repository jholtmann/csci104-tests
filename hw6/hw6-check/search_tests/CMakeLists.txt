add_executable(search_test search_utils.cpp search_tests.cpp)
target_link_libraries(search_test testing_utils gtest gtest_main)
gtest_add_tests(search_test "" AUTO)

# make sure user code gets remade first
add_dependencies(search_test user_makefile)
