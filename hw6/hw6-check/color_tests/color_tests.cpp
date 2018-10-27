#include "gtest/gtest.h"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "color_utils.h"

using namespace std;

class ColorTest : public ::testing::Test {
protected:
  size_t letter_count;
  size_t row_count;
  size_t col_count;
  vector<size_t> expected;
  string map;
  string testName;

  string output;

  void SetUp(string testName, string map, size_t letter_count, size_t row_count, size_t col_count, vector<size_t> expected) {
    this->testName = testName;
    this->map = map;
    this->letter_count = letter_count;
    this->row_count = row_count;
    this->col_count = col_count;
    this->expected = expected;
  }

  virtual void TearDown() {
    EXPECT_TRUE(runColor(output, testName, letter_count, row_count, col_count, map));

    stringstream ss;
    for (size_t i = 0; i < letter_count; i++) {
      ss << (char)(65 + i) << " " << expected[i] << endl;
    }

    EXPECT_TRUE(output.find(ss.str()) != string::npos);
  }
};

TEST_F(ColorTest, Provided) {
  string s =  "AAAAAACCCCCCC\n"
              "AAAAAACCCCCCD\n"
              "BBBAAACCCCCDD\n"
              "BBAAAACCEEDDD\n"
              "BBBBBACDEEEDD\n"
              "BBBBBBDDDDDDD\n";
  SetUp("Provided", s, 5, 6, 13, {1, 2, 2, 1, 3});
}

TEST_F(ColorTest, Provided2) {
  string s =  "FFFFFFFF\n"
              "FEEEDDDF\n"
              "FAABBCCF\n"
              "FFFFFFFF\n";
  SetUp("Provided2", s, 6, 4, 8, {1, 2, 3, 1, 3, 4});
}

TEST_F(ColorTest, Provided3) {
  string s =  "FFFFFFFFFFFFFFF\n"
              "FFFFFFFFFFFFFFF\n"
              "FFEEEDDDDDDDDFF\n"
              "FFEEEDDDDDDDDFF\n"
              "FFEEEDDDDDDDDFF\n"
              "FFAABBBBBBCCCFF\n"
              "FFAABBBBBBCCCFF\n"
              "FFAABBBBBBCCCFF\n"
              "FFFFFFFFFFFFFFF\n"
              "FFFFFFFFFFFFFFF\n";
  SetUp("Provided2", s, 6, 10, 15, {1, 2, 3, 1, 3, 4});
}
