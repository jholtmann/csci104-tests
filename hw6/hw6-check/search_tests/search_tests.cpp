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
    // output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());

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

TEST_F(SearchTest, AllAs) {
  string s =  "AAAAAAAAAAAAA \n"
              "AAAAAAAAAAAAA \n"
              "AAAAAAAAAAAAA \n"
              "AAAAAAAAAAAAA \n"
              "AAAAAAAAAAAAA \n"
              "AAAAAAAAAAAAA \n";

  SetUp("Provided", s, 1, 6, 13, 78);
}

TEST_F(SearchTest, Provided2) {
  string s =  "FFFFFFFF \n"
              "FEEEDDDF \n"
              "FAABBCCF \n"
              "FFFFFFFF \n";

  SetUp("Provided2", s, 6, 4, 8, 20);
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
}

TEST_F(SearchTest, NarrowPath) {
  string s =  "ABACABABAB\n"
              "ABACABABAB\n"
              "ABACABABAB\n"
              "ABACCCCCCC\n"
              "ABACABABAB\n";

  SetUp("NarrowPath", s, 3, 5, 10, 11);
}

TEST_F(SearchTest, UniqueLetters) {
  string s =  "ABCDEFGHIJ \n"
              "KLMNOPQRST \n";

  SetUp("UniqueLetters", s, 20, 2, 10, 1);
}

TEST_F(SearchTest, TwoByTwo) {
  string s =  "AC \n"
              "AB \n";

  SetUp("TwoByTwo", s, 3, 2, 2, 2);
}

TEST_F(SearchTest, BorderingAcross) {
  string s =  "AAAAAABBBB\n"
              "AAAAAABBBB\n"
              "BBBBBBAAAA\n"
              "BBAAAABBCC\n"
              "BBBBBABACC\n";

  SetUp("BorderingAcross", s, 3, 5, 10, 13);
}

TEST_F(SearchTest, Heart) {
    string s =  "_____8888888888_____________________\n"
                "____888888888888888_________________\n"
                "__888888822222228888________________\n"
                "_88888822222222288888_______________\n"
                "888888222222222228888822228888______\n"
                "888882222222222222288222222222888___\n"
                "8888822222222222222222222222222288__\n"
                "_8888822222222222222222222222222_88_\n"
                "__88888222222222222222222222222__888\n"
                "___888822222222222222222222222___888\n"
                "____8888222222222222222222222____888\n"
                "_____8888222222222222222222_____888_\n"
                "______8882222222222222222_____8888__\n"
                "_______888822222222222______888888__\n"
                "________8888882222______88888888____\n"
                "_________888888_____888888888_______\n"
                "__________88888888888888____________\n"
                "___________8888888888_______________\n"
                "____________8888888_________________\n"
                "_____________88888__________________\n"
                "______________888___________________\n"
                "_______________8____________________\n";
    SetUp("Heart", s, 4, 22, 36, 224);
}
