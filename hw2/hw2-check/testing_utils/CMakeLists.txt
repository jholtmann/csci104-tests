
# build kwsys dependency library
add_definitions(-D_DEFAULT_SOURCE)
set(KWSYS_NAMESPACE kwsys)
set(KWSYS_USE_SystemTools TRUE)
set(KWSYS_USE_RegularExpression TRUE)
set(KWSYS_USE_Process TRUE)
set(KWSYS_HEADER_ROOT ${CMAKE_CURRENT_BINARY_DIR}/generated_headers)
add_subdirectory(kwsys)

set(TESTING_UTILS_SOURCES
	circular_list_utils.cpp
	runtime_evaluator.cpp
	random_generator.cpp
	selection_sort_utils.cpp
	misc_utils.cpp
	user_code_runner.cpp
	rang.h
	duck_duck_goose_utils.cpp)

add_library(testing_utils STATIC ${TESTING_UTILS_SOURCES})
target_include_directories(testing_utils PUBLIC . ${CMAKE_CURRENT_BINARY_DIR}/generated_headers)
target_link_libraries(testing_utils hw2_user_code gtest kwsys)

# tell utils library about the directory structure
target_compile_definitions(testing_utils PUBLIC TEST_BINARY_DIR=\"${CMAKE_BINARY_DIR}\" USER_CODE_DIR=\"${HW2_DIR}\" DDG_EXECUTABLE=\"$<TARGET_FILE:duck_duck_goose>\")
