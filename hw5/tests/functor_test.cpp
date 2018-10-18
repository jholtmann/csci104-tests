#include "gtest/gtest.h"

#include "../functor.h"

#include <vector>

using namespace std;

TEST(NumStrComp, Simple) {
  NumStrComp comp;

  string s1 = "1";
  string s2 = "2";

  EXPECT_TRUE(comp(s1, s2) == true);
}

TEST(NumStrComp, SimpleTwo) {
  NumStrComp comp;

  string s1 = "111";
  string s2 = "222";

  EXPECT_TRUE(comp(s1, s2) == true);
}

TEST(NumStrComp, SimpleAlphabet) {
  NumStrComp comp;

  string s1 = "A";
  string s2 = "B";

  EXPECT_TRUE(comp(s1, s2) == true);
}

TEST(NumStrComp, SimpleAlphabetFalse) {
  NumStrComp comp;

  string s1 = "B";
  string s2 = "A";

  EXPECT_TRUE(comp(s1, s2) == false);
}

TEST(NumStrComp, ComplexAlphabet) {
  NumStrComp comp;

  string s1 = "ABBABAFHWEFWHWEF";
  string s2 = "ZZZZZZZZZZZZZZZZ";

  EXPECT_TRUE(comp(s1, s2) == true);
}

TEST(NumStrComp, ComplexAlphabetFalse) {
  NumStrComp comp;

  string s1 = "ZZZZZZZZZZZZZZZZ";
  string s2 = "ABBABAFHWEFWHWEF";

  EXPECT_TRUE(comp(s1, s2) == false);
}

TEST(NumStrComp, LowerCase) {
  NumStrComp comp;

  string s1 = "aaa";
  string s2 = "ddd";

  EXPECT_TRUE(comp(s1, s2) == true);
}

TEST(NumStrComp, MixedCase) {
  NumStrComp comp;

  string s1 = "AaBbCcDd";
  string s2 = "AaBbCcDda";

  EXPECT_TRUE(comp(s1, s2) == true);
}

TEST(NumStrComp, OtherSymbols) {
  NumStrComp comp;

  string s1 = "!.[]{}\\~`===`==``=`..,,--.,Z-,--,--.";
  string s2 = "Y2";

  EXPECT_TRUE(comp(s1, s2) == true);
}

TEST(NumStrComp, MixedCaseAlphanumeric) {
  NumStrComp comp;

  string s1 = "Z";
  string s2 = "Y2";

  EXPECT_TRUE(comp(s1, s2) == true);
}

TEST(NumStrComp, MixedCaseAlphanumericTwo) {
  NumStrComp comp;

  string s1 = "A1aBb4C7cDd2";
  string s2 = "A2aBb4C8cDdb1";

  EXPECT_TRUE(comp(s1, s2) == true);
}
