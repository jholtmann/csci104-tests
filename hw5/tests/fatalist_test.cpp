#include "gtest/gtest.h"

#include "../fatalist.cpp"

#include <vector>

using namespace std;

/*** Test Fixture ***/
// Base class; no default assertion run at end
class FatalistTest : public ::testing::Test {
protected:
    vector<pair<int,int>> tmp;
};

// Use this if expect true
class FatalistTestTrue : public FatalistTest {
protected:
    void TearDown() {
        EXPECT_TRUE(FatalistHypothesis(tmp));
    }
};

// Use this if expect false
class FatalistTestFalse : public FatalistTest {
protected:
    void TearDown() {
        EXPECT_TRUE(!FatalistHypothesis(tmp));
    }
};

/*** Test Definitions ***/
TEST_F (FatalistTestTrue, SimpleTest) {
  tmp.emplace_back(50,90);
  tmp.emplace_back(30,20);
  tmp.emplace_back(30,20);
}

TEST_F (FatalistTestTrue, SimpleTestTwo) {
  tmp.emplace_back(50,90);
  tmp.emplace_back(30,20);
  tmp.emplace_back(29,20);
}

TEST_F (FatalistTestTrue, Unordered) {
  tmp.emplace_back(28,10);
  tmp.emplace_back(90,90);
  tmp.emplace_back(29,70);
}

TEST_F(FatalistTestTrue, empty) {
  // True because we need to disprove in order for it to be false
  // tl;dr need counter-example
}

TEST_F(FatalistTestTrue, OneStudentBoiSame) {
    tmp.emplace_back(100, 100);
}

TEST_F(FatalistTestTrue, OneStudentBoiMismatch) {
    tmp.emplace_back(70, 71);
}

TEST_F(FatalistTestTrue, TwoStudentsTrue) {
    tmp.emplace_back(70, 71);
    tmp.emplace_back(90, 87);
}

TEST_F(FatalistTestTrue, TwoStudentsTrueClose) {
    tmp.emplace_back(70, 71);
    tmp.emplace_back(71, 71); // True because 71 >= 71
}

TEST_F(FatalistTestFalse, TwoStudentsFalse) {
    tmp.emplace_back(70, 71);
    tmp.emplace_back(52, 87); // False because 52 < 70
}

TEST_F(FatalistTestTrue, TwoStudentsSame) {
    tmp.emplace_back(69, 69);
    tmp.emplace_back(69, 69);
}

TEST_F(FatalistTestTrue, TwoStudentsSimilar) {
    tmp.emplace_back(69, 1337);
    tmp.emplace_back(69, 420);
}

TEST_F(FatalistTestTrue, ThreeStudentsTrue) {
    tmp.emplace_back(70, 70);
    tmp.emplace_back(80, 80);
    tmp.emplace_back(90, 90);
}

TEST_F(FatalistTestFalse, ThreeStudentsFalse) {
    tmp.emplace_back(70, 70);
    tmp.emplace_back(80, 80);
    tmp.emplace_back(90, 79); // False because 79 < 80
}

TEST_F(FatalistTestTrue, ThreeStudentsTwoSameTrue) {
    tmp.emplace_back(70, 81);
    tmp.emplace_back(70, 80);
    tmp.emplace_back(71, 82); 
}

TEST_F(FatalistTestFalse, ThreeStudentsTwoSameFalse) {
    tmp.emplace_back(70, 83);
    tmp.emplace_back(70, 80);
    tmp.emplace_back(71, 82); // False because 79 < 80
}

TEST_F(FatalistTestTrue, ManyStudentsSimpleTrue) {
    for(int i=0;i < 1000;i++) {
        tmp.emplace_back(i, i);
    }
}

TEST_F(FatalistTestFalse, ManyStudentsSimpleFalse) {
    for(int i=0;i < 1000;i++) {
        tmp.emplace_back(i, i);
    }
    // False because 500 > 499 (104 score), but 0 < 499 (170 score)
    tmp.emplace_back(500, 0);
}

TEST_F(FatalistTestTrue, StressTrue) {
    for(int i=0;i < 100000;i++) {
        tmp.emplace_back(i, i);
    }
}

TEST_F(FatalistTestFalse, StressFalse) {
    for(int i=0;i < 100000;i++) {
        tmp.emplace_back(i, i);
    }
    // False because 500 > 499 (104 score), but 0 < 499 (170 score)
    tmp.emplace_back(500, 0);
}

