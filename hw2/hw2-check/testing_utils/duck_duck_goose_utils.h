//
// Utilities for the Duck Duck Goose tests
//

#ifndef CS104_HW2_TEST_SUITE_DUCK_DUCK_GOOSE_UTILS_H
#define CS104_HW2_TEST_SUITE_DUCK_DUCK_GOOSE_UTILS_H

#include "user_code_runner.h"

#include <gtest/gtest.h>

#include <string>

// runs the user's duck duck goose executable with the given parameters.
// returns a pair of:
// -- an AssertionResult describing any errors in the execution
// -- a pointer to string containing the results of the program
// params:
// -- itPlayerID: ID of player who starts as it
// -- otherPlayers: IDs of the other players in the game
// -- testName: name for this test.  Test files will be created under hw2-check/duck_duck_goose_tests/testFiles/<testName>
// -- output: result of the program is written to this string
testing::AssertionResult runDuckDuckGooseProgram(unsigned int randomSeed, int itPlayerID, std::vector<int> otherPlayers, std::string testName, std::string & output);


#endif //CS104_HW2_TEST_SUITE_DUCK_DUCK_GOOSE_UTILS_H
