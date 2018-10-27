#include "gtest/gtest.h"

// Base class; no defaults (as of now)

class ColorTest : public ::testing::Test {
protected:
  int letter_count;
  int row_count;
  int col_count;
  vector<int> expected;
  string map;
  string testName;

  string output;

  void SetUp(string testName, string map, int letter_count, int row_count, int col_count, vector<int> expected) {
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


/*** Test Definitions ***/
TEST_F (SearchTest, simple) {

}
