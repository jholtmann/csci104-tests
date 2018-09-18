//
// Utilities for the Parser tests
//

#ifndef CS104_HW3_TEST_SUITE_PARSER_UTILS_H
#define CS104_HW3_TEST_SUITE_PARSER_UTILS_H

#include "user_code_runner.h"

#include <gtest/gtest.h>

#include <string>

// runs the user's parser executable with the given string "equation" as the input file.
testing::AssertionResult runParserProgram(std::string equation, std::string testName, std::string &output);

#endif
