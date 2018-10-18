#include "gtest/gtest.h"

#include "../fatalist.cpp"

#include <vector>

using namespace std;

TEST (Fatalist, SimpleTest) {
  vector<pair<int, int>> test;
  test.push_back(make_pair(50,90));
  test.push_back(make_pair(30,20));
  test.push_back(make_pair(30,20));

  EXPECT_TRUE(FatalistHypothesis(test) == 1);
}

TEST (Fatalist, SimpleTestTwo) {
  vector<pair<int, int>> test;
  test.push_back(make_pair(50,90));
  test.push_back(make_pair(30,20));
  test.push_back(make_pair(29,20));

  EXPECT_TRUE(FatalistHypothesis(test) == 0);
}

TEST (Fatalist, Unordered) {
  vector<pair<int, int>> test;
  test.push_back(make_pair(28,10));
  test.push_back(make_pair(90,90));
  test.push_back(make_pair(29,70));

  EXPECT_TRUE(FatalistHypothesis(test) == 1);
}

TEST(Basic, empty) {
    std::vector<std::pair<int,int>> tmp;

    ASSERT_EQ(FatalistHypothesis(tmp),false);
}

TEST(Basic, TwoStudentsTrue) {
    std::vector<std::pair<int,int>> tmp;
    tmp.emplace_back(70, 71);
    tmp.emplace_back(90, 87);

    ASSERT_EQ(FatalistHypothesis(tmp), true);
}

TEST(Basic, TwoStudentsTrueClose) {
    std::vector<std::pair<int,int>> tmp;
    tmp.emplace_back(70, 71);
    tmp.emplace_back(71, 71); // True because 71 >= 71

    ASSERT_EQ(FatalistHypothesis(tmp), true);
}

TEST(Basic, TwoStudentsFalse) {
    std::vector<std::pair<int,int>> tmp;
    tmp.emplace_back(70, 71);
    tmp.emplace_back(52, 87); // False because 52 < 70

    ASSERT_EQ(FatalistHypothesis(tmp), false);
}

TEST(Basic, TwoStudentsSame) {
    std::vector<std::pair<int,int>> tmp;
    tmp.emplace_back(69, 69);
    tmp.emplace_back(69, 69);

    ASSERT_EQ(FatalistHypothesis(tmp), false);
}

TEST(Basic, ThreeStudentsTrue) {
    std::vector<std::pair<int,int>> tmp;
    tmp.emplace_back(70, 70);
    tmp.emplace_back(80, 80);
    tmp.emplace_back(90, 90);

    ASSERT_EQ(FatalistHypothesis(tmp), true);
}

TEST(Basic, ThreeStudentsFalse) {
    std::vector<std::pair<int,int>> tmp;
    tmp.emplace_back(70, 70);
    tmp.emplace_back(80, 80);
    tmp.emplace_back(90, 79); // False because 79 < 80

    ASSERT_EQ(FatalistHypothesis(tmp), false);
}

TEST(Basic, ManyStudentsSimpleTrue) {
    std::vector<std::pair<int,int>> tmp;
    for(int i=0;i < 1000;i++) {
        tmp.emplace_back(i, i);
    }

    ASSERT_EQ(FatalistHypothesis(tmp), true);
}

TEST(Basic, ManyStudentsSimpleFalse) {
    std::vector<std::pair<int,int>> tmp;
    for(int i=0;i < 1000;i++) {
        tmp.emplace_back(i, i);
    }
    // False because 500 > 499 (104 score), but 0 < 499 (170 score)
    tmp.emplace_back(500, 0);

    ASSERT_EQ(FatalistHypothesis(tmp), false);
}
