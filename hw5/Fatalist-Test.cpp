//
// Fatalist-Test
//
//     Created: 10/17/18
//      Author: Matthew Treadwell 
// 
//

#include <gtest/gtest.h>
#include "fatalist.cpp"

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

    ASSERT_EQ(FatalistHypothesis(tmp), true);
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
    for(int i=0;i < 100;i++) {
        tmp.emplace_back(i, i);
    }
    // False because 500 > 499 (104 score), but 0 < 499 (170 score)
    tmp.emplace_back(500, 0);

    ASSERT_EQ(FatalistHypothesis(tmp), true);
}