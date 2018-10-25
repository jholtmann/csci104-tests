#include <gtest/gtest.h>
#include "search_utils.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

/*** Test Fixture ***/
class SearchTest : public ::testing::Test {
protected:
  int letter_count;
  int row_count;
  int col_count;
  int expected;
  string map;
  string testName;

  string output;

  void SetUp(string testName, string map, int letter_count, int row_count, int col_count, int expected) {
    this->testName = testName;
    this->map = map;
    this->letter_count = letter_count;
    this->row_count = row_count;
    this->col_count = col_count;
    this->expected = expected;
  }

  virtual void TearDown() {
    EXPECT_TRUE(runSearch(output, testName, letter_count, row_count, col_count, map));

    // Erase newline characters
    output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());

    EXPECT_EQ(stoi(output), expected);
  }
};

TEST_F(SearchTest, Provided) {
  string s =  "AAAAAABBBBBBB \n"
              "AAAAAABBBBBBA \n"
              "BBBAAABBBBBAA \n"
              "BBAAAABBCCAAA \n"
              "BBBBBABACCCAA \n"
              "BBBBBBAAAAAAA \n";

  SetUp("Provided", s, 3, 6, 13, 21);
}
