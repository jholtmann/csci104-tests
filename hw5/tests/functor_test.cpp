#include "gtest/gtest.h"

#include "../functor.h"

#include <vector>

using namespace std;

class NumStrCompTest : public ::testing::Test {
protected:
    NumStrComp comp;
    string s1, s2;
};

class NumStrCompTestTrue: public NumStrCompTest {
protected:
    void TearDown() {
      EXPECT_TRUE(comp(s1, s2));
    }
};

class NumStrCompTestFalse: public NumStrCompTest {
protected:
    void TearDown() {
      EXPECT_TRUE(!comp(s1, s2));
    }
};

class NumStrCompTestTie: public NumStrCompTest {
protected:
    void TearDown() {
      // Use standard string comparison
      EXPECT_EQ(comp(s1,s2),s1 < s2);
    }
};

TEST_F(NumStrCompTestTrue, Simple) {
  s1 = "1";
  s2 = "2";
}

TEST_F(NumStrCompTestTrue, SimpleTwo) {
  s1 = "111";
  s2 = "222";
}

TEST_F(NumStrCompTestTrue, SimpleAlphabet) {
  s1 = "A";
  s2 = "B";
}

TEST_F(NumStrCompTestTrue, mixedClose1) {
  s1 = "1";
  s2 = "Ao";
}

TEST_F(NumStrCompTestFalse, mixedClose2) {
  s1 = "A";
  s2 = "1111111111";
}

TEST_F(NumStrCompTestFalse, SimpleAlphabetFalse) {
  s1 = "B";
  s2 = "A";
}

TEST_F(NumStrCompTestTrue, ComplexAlphabet) {
  s1 = "ABBABAFHWEFWHWEF";
  s2 = "ZZZZZZZZZZZZZZZZ";
}

TEST_F(NumStrCompTestFalse, ComplexAlphabetFalse) {
  s1 = "ZZZZZZZZZZZZZZZZ";
  s2 = "ABBABAFHWEFWHWEF";
}

TEST_F(NumStrCompTestTrue, LowerCase) {
  s1 = "aaa";
  s2 = "ddd";
}

TEST_F(NumStrCompTestTrue, MixedCase) {
  s1 = "AaBbCcDd";
  s2 = "AaBbCcDda";
}

TEST_F(NumStrCompTestTrue, OtherSymbols) {
  s1 = "!.[]{}\\~`===`==``=`..,,--.,Z-,--,--.";
  s2 = "Y2";
}

TEST_F(NumStrCompTestTrue, MixedCaseAlphanumeric) {
  s1 = "Z";
  s2 = "Y2";
}

TEST_F(NumStrCompTestTrue, MixedCaseAlphanumericTwo) {
  s1 = "A1aBb4C7cDd2";
  s2 = "A2aBb4C8cDdb1";
}

TEST_F(NumStrCompTestTie, MixedCaseAlphanumericShuffleSame) {
  s1 = "IAmMadScientist7";
  s2 = "imadam7scientist";
}

TEST_F(NumStrCompTestTie, MixedCaseSame) {
  s1 = "a";
  s2 = "A";
}

TEST_F(NumStrCompTestTie, AlphanumericSame) {
  s1 = "19";
  s2 = "A";
}

