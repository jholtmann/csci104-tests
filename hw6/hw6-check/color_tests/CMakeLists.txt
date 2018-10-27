add_executable(color_test color_utils.cpp color_tests.cpp)
target_link_libraries(color_test testing_utils gtest gtest_main)
gtest_add_tests(color_test "" AUTO)

# make sure user code gets remade first
add_dependencies(color_test user_makefile)
