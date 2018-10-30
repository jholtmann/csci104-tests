cmake_minimum_required(VERSION 3.1)

message("########################################################")
message("                 JTEST HW3 Test Suite")
message("########################################################")

project(JTEST-CS104-HW3-Test-Suite C CXX)

# pick up include files
# ----------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/test_cmake_lib)

include(Policies NO_POLICY_SCOPE)
include(Utils)
include(Shorthand)
include(LibraryUtils)
include(104CompileFlags)

# setup Valgrind
# ----------------------------------------------------------

find_program(VALGRIND NAMES valgrind DOC "Path to valgrind executable")
import_executable(valgrind ${VALGRIND})

set(VALGRIND_ARGS --tool=memcheck
	--leak-check=yes
	--error-exitcode=42   # force valgrind to report an error when there are Valgrind errors
	--trace-children=no) # don't valgrind child processes, we control manually which processes are valground

# find GTest
# ----------------------------------------------------------

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

import_libraries(gtest LIBRARIES ${GTEST_LIBRARIES} Threads::Threads INCLUDES ${GTEST_INCLUDE_DIRS})
import_libraries(gtest_main LIBRARIES ${GTEST_MAIN_LIBRARIES} Threads::Threads INCLUDES ${GTEST_INCLUDE_DIRS})

include(CustomTests)
enable_testing()

# find user code dir
# ----------------------------------------------------------

if(NOT DEFINED HW3_DIR)

	file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_SOURCE_DIR}/../*.cpp")

	if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
		message(FATAL_ERROR "Cannot find source files in parent directory.  Either move this test directory to your hw2 dir, or run CMake with the \"-DHW3_DIR=<path to hw2>\" argument to use a custom location")
	else()
		get_filename_component(PARENT_DIR_REALPATH "${CMAKE_SOURCE_DIR}/.." REALPATH)
		message(STATUS "HW3_DIR autoset to ${PARENT_DIR_REALPATH}")
		set(HW3_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw2 assignment directory")
	endif()
endif()

# build loose user code as a CMake library
# ----------------------------------------------------------

set(HW2_SOURCES
	${HW3_DIR}/selection_sort.cpp
	${HW3_DIR}/circular_list_int.cpp
	${HW3_DIR}/duck_duck_goose.cpp)

# first check that we have the right sources
foreach(HW2_SOURCE ${HW2_SOURCES})
	if(NOT EXISTS ${HW2_SOURCE})
		message(FATAL_ERROR "Cannot find required source file ${HW2_SOURCE}")
	endif()
endforeach()

# now build user code into a CMake library
add_library(hw2_user_code STATIC ${HW2_SOURCES})
target_include_directories(hw2_user_code PUBLIC ${HW3_DIR})

# disable main function in duck_duck_goose.cpp
target_compile_definitions(hw2_user_code PRIVATE main=disabled_main)

# build user executable
# ----------------------------------------------------------

# add_executable(duck_duck_goose ${HW3_DIR}/duck_duck_goose.cpp ${HW3_DIR}/circular_list_int.cpp)

# build testing utils lib
# ----------------------------------------------------------

add_subdirectory(testing_utils)


# build actual tests
# ----------------------------------------------------------
add_subdirectory(selection_sort_tests)
add_subdirectory(circular_list_tests)
add_subdirectory(duck_duck_goose_tests)
