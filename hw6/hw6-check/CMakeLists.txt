cmake_minimum_required(VERSION 3.1)

message("########################################################")
message("                 CS104 HW6 Test Suite")
message("########################################################")

project(CS104-HW6-Test-Suite C CXX)

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

if(NOT DEFINED HW6_DIR)

	file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_SOURCE_DIR}/../*.cpp")

	if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
		message(FATAL_ERROR "Cannot find source files in parent directory.  Either move this test directory to your hw6 dir, or run CMake with the \"-DHW6_DIR=<path to hw6>\" argument to use a custom location")
	else()
		get_filename_component(PARENT_DIR_REALPATH "${CMAKE_SOURCE_DIR}/.." REALPATH)
		message(STATUS "HW6_DIR autoset to ${PARENT_DIR_REALPATH}")
		set(HW6_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw6 assignment directory")
	endif()
endif()

# build loose user code as a CMake library
# Note: add any additional .cpp files you made here
# ----------------------------------------------------------

set(HW6_SOURCES
	${HW6_DIR}/MinHeap.h
	${HW6_DIR}/search.cpp
	${HW6_DIR}/coloring.cpp)

# first check that we have the right sources
foreach(HW6_SOURCE ${HW6_SOURCES})
	if(NOT EXISTS ${HW6_SOURCE})
		message(FATAL_ERROR "Cannot find required source file ${HW6_SOURCE}")
	endif()
endforeach()

# now build user code into a CMake library
add_library(hw6_user_code STATIC ${HW6_SOURCES})
target_include_directories(hw6_user_code PUBLIC ${HW6_DIR})

# build user parser executable using make
# ----------------------------------------------------------

set(USER_CODE_EXECUTABLE ${HW6_DIR}/search)

# find all c++ files as dependencies, so that the code can be remade
file(GLOB_RECURSE USER_CODE_DIR_FILES "${HW6_DIR}/*.cpp" "${HW6_DIR}/*.h")

add_custom_command(OUTPUT ${USER_CODE_EXECUTABLE}
		COMMAND make
		WORKING_DIRECTORY ${HW6_DIR}
		VERBATIM
		DEPENDS ${USER_CODE_DIR_FILES}
		COMMENT "Running make in hw6 directory...")

add_custom_target(user_makefile
		ALL
		DEPENDS ${USER_CODE_EXECUTABLE})

add_subdirectory(testing_utils)

# build actual tests
# ----------------------------------------------------------
add_subdirectory(search_tests)
add_subdirectory(color_tests)
add_subdirectory(heap_tests)
