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

TEST_F(NumStrCompTestFalse, SimpleAlphabetFalse) {
  s1 = "B";
  s2 = "A";
}

TEST_F(NumStrCompTestTrue, ComplexAlphabet) {
  s1 = "ABBABAFHWEFWHWEF";
  s2 = "ZZZZZZZZZZZZZZZZ";
}

TEST_F(NumStrCompTestTrue, ComplexAlphabetFalse) {
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

TEST_F(NumStrCompTest, OtherSymbols) {
  s1 = "!.[]{}\\~`===`==``=`..,,--.,Z-,--,--.";
  s2 = "Y2";
}

TEST_F(NumStrCompTest, MixedCaseAlphanumeric) {
  s1 = "Z";
  s2 = "Y2";
}

TEST_F(NumStrCompTest, MixedCaseAlphanumericTwo) {
  s1 = "A1aBb4C7cDd2";
  s2 = "A2aBb4C8cDdb1";
}
