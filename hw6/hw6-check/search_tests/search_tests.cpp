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

  virtual void runTest() {
    EXPECT_TRUE(runSearch(output, testName, letter_count, row_count, col_count, map));

    try {
      EXPECT_EQ(stoi(output), expected);
    } catch (exception& e) {
      cerr << "Failed to parse output" << endl;
      cerr << "Your program output: " << output << endl;
      FAIL();
    }
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
  runTest();
}

TEST_F(SearchTest, Provided2) {
  string s =  "FFFFFFFF \n"
              "FEEEDDDF \n"
              "FAABBCCF \n"
              "FFFFFFFF \n";

  SetUp("Provided2", s, 6, 4, 8, 20);
  runTest();
}

TEST_F(SearchTest, Provided3) {
  string s =    "FFFFFFFFFFFFFFF\n"
                "FFFFFFFFFFFFFFF\n"
                "FFEEEDDDDDDDDFF\n"
                "FFEEEDDDDDDDDFF\n"
                "FFEEEDDDDDDDDFF\n"
                "FFAABBBBBBCCCFF\n"
                "FFAABBBBBBCCCFF\n"
                "FFAABBBBBBCCCFF\n"
                "FFFFFFFFFFFFFFF\n"
                "FFFFFFFFFFFFFFF\n";

  SetUp("Provided3", s, 6, 10, 15, 84);
  runTest();
}

TEST_F(SearchTest, AllAs) {
  string s =  "AAAAAAAAAAAAA \n"
              "AAAAAAAAAAAAA \n"
              "AAAAAAAAAAAAA \n"
              "AAAAAAAAAAAAA \n"
              "AAAAAAAAAAAAA \n"
              "AAAAAAAAAAAAA \n";

  SetUp("AllAs", s, 1, 6, 13, 78);
  runTest();
}

TEST_F(SearchTest, NarrowPath) {
  string s =  "ABACABABAB\n"
              "ABACABABAB\n"
              "ABACABABAB\n"
              "ABACCCCCCC\n"
              "ABACABABAB\n";

  SetUp("NarrowPath", s, 3, 5, 10, 11);
  runTest();
}

TEST_F(SearchTest, UniqueLetters) {
  string s =  "ABCDEFGHIJ \n"
              "KLMNOPQRST \n";

  SetUp("UniqueLetters", s, 20, 2, 10, 1);
  runTest();
}

TEST_F(SearchTest, TwoByTwo) {
  string s =  "AC \n"
              "AB \n";

  SetUp("TwoByTwo", s, 3, 2, 2, 2);
  runTest();
}

TEST_F(SearchTest, BorderingAcross) {
  string s =  "AAAAAABBBB\n"
              "AAAAAABBBB\n"
              "BBBBBBAAAA\n"
              "BBAAAABBCC\n"
              "BBBBBABACC\n";

  SetUp("BorderingAcross", s, 3, 5, 10, 13);
  runTest();
}

TEST_F(SearchTest, Heart) {
    string s =  "BBBBBAAAAAAAAAABBBBBBBBBBBBBBBBBBBBB\n"
                "BBBBAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBB\n"
                "BBAAAAAAACCCCCCCAAAABBBBBBBBBBBBBBBB\n"
                "BAAAAAACCCCCCCCCAAAAABBBBBBBBBBBBBBB\n"
                "AAAAAACCCCCCCCCCCAAAAACCCCAAAABBBBBB\n"
                "AAAAACCCCCCCCCCCCCCAACCCCCCCCCAAABBB\n"
                "AAAAACCCCCCCCCCCCCCCCCCCCCCCCCCCAABB\n"
                "BAAAAACCCCCCCCCCCCCCCCCCCCCCCCCCBAAB\n"
                "BBAAAAACCCCCCCCCCCCCCCCCCCCCCCCBBAAA\n"
                "BBBAAAACCCCCCCCCCCCCCCCCCCCCCCBBBAAA\n"
                "BBBBAAAACCCCCCCCCCCCCCCCCCCCCBBBBAAA\n"
                "BBBBBAAAACCCCCCCCCCCCCCCCCCBBBBBAAAB\n"
                "BBBBBBAAACCCCCCCCCCCCCCCCBBBBBAAAABB\n"
                "BBBBBBBAAAACCCCCCCCCCCBBBBBBAAAAAABB\n"
                "BBBBBBBBAAAAAACCCCBBBBBBAAAAAAAABBBB\n"
                "BBBBBBBBBAAAAAABBBBBAAAAAAAAABBBBBBB\n"
                "BBBBBBBBBBAAAAAAAAAAAAAABBBBBBBBBBBB\n"
                "BBBBBBBBBBBAAAAAAAAAABBBBBBBBBBBBBBB\n"
                "BBBBBBBBBBBBAAAAAAABBBBBBBBBBBBBBBBB\n"
                "BBBBBBBBBBBBBAAAAABBBBBBBBBBBBBBBBBB\n"
                "BBBBBBBBBBBBBBAAABBBBBBBBBBBBBBBBBBB\n"
                "BBBBBBBBBBBBBBBABBBBBBBBBBBBBBBBBBBB\n";
  SetUp("Heart", s, 3, 22, 36, 224);
  runTest();
}
