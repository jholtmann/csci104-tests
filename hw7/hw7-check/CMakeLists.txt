cmake_minimum_required(VERSION 3.1)

message("########################################################")
message("                 CS104 HW7 Test Suite")
message("########################################################")

project(CS104-HW7-Test-Suite C CXX)

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

if(NOT DEFINED HW7_DIR)

	file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_SOURCE_DIR}/../*.h")

	if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
		message(FATAL_ERROR "Cannot find source files in parent directory.  Either move this test directory to your hw7 dir, or run CMake with the \"-DHW7_DIR=<path to hw7>\" argument to use a custom location")
	else()
		get_filename_component(PARENT_DIR_REALPATH "${CMAKE_SOURCE_DIR}/.." REALPATH)
		message(STATUS "HW7_DIR autoset to ${PARENT_DIR_REALPATH}")
		set(HW7_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw7 assignment directory")
	endif()
endif()

# build loose user code as a CMake library
# Note: add any additional .cpp files you made here
# ----------------------------------------------------------

set(HW7_SOURCES
	${HW7_DIR}/avlbst.h
	${HW7_DIR}/bst.h
	${HW7_DIR}/print_bst.h
	${HW7_DIR}/rotateBST.h)

# first check that we have the right sources
foreach(HW7_SOURCE ${HW7_SOURCES})
	if(NOT EXISTS ${HW7_SOURCE})
		message(FATAL_ERROR "Cannot find required source file ${HW7_SOURCE}")
	endif()
endforeach()

# now build user code into a CMake library
add_library(hw7_user_code STATIC ${HW7_SOURCES})
set_target_properties(hw7_user_code PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(hw7_user_code PUBLIC ${HW7_DIR})

add_subdirectory(testing_utils)

# build actual tests
# ----------------------------------------------------------
add_subdirectory(bst_tests)
add_subdirectory(rotate_tests)
add_subdirectory(avl_tests)
