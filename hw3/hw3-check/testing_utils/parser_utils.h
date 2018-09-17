//
// Utilities for the Parser tests
//

#ifndef CS104_HW2_TEST_SUITE_PARSER_UTILS_H
#define CS104_HW2_TEST_SUITE_PARSER_UTILS_H

#include "user_code_runner.h"

#include <gtest/gtest.h>

#include <string>

// runs the user's parser executable with the given string "equation" as the input file.
testing::AssertionResult runParserProgram(std::string equation, std::string testName);

#endif //CS104_HW2_TEST_SUITE_DUCK_DUCK_GOOSE_UTILS_H
