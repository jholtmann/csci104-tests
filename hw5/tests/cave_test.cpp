//
// Cave-Test
//
//     Created: 10/17/18
//      Author: Matthew Treadwell 
// 
//
// How To Use:
// 1. Inside cave.cpp,
//    Copy main function into function called ropeCheck(string input)
//    Delete any cin/getLine statements
// 2. Comment out main function
// Flaws:
// These tests rely on checking stdout
// can't detect multiple calls to stdout
// (example: doing cout << "rolled up" 500 times will pass)

#include <gtest/gtest.h>
#include "../cave.cpp"

// Setup test fixture
class Basic : public ::testing::Test {
public:
    Basic() {
        testing::internal::CaptureStdout();
    }
};

// These subclasses define the program's result
class rolledUp : public Basic {
protected:
    std::string alpha;
    void TearDown() override {
        alpha = testing::internal::GetCapturedStdout();
        EXPECT_TRUE(alpha.find("not")==std::string::npos);
        EXPECT_TRUE(alpha.find("invalid")==std::string::npos);
        EXPECT_TRUE(alpha.find("rolled up")!=std::string::npos);
    }
};

class notRolledUp : public Basic {
protected:
    std::string alpha;
    void TearDown() override {
        alpha = testing::internal::GetCapturedStdout();
        EXPECT_TRUE(alpha.find("invalid") == std::string::npos);
        EXPECT_TRUE(alpha.find("not rolled up") != std::string::npos);
    }
};

class invalid : public Basic {
protected:
    std::string alpha;
    void TearDown() override {
        alpha = testing::internal::GetCapturedStdout();
        EXPECT_TRUE(alpha.find("not") == std::string::npos);
        EXPECT_TRUE(alpha.find("rolled up") == std::string::npos);
        EXPECT_TRUE(alpha.find("invalid") != std::string::npos);
    }
};

/*** Define Tests***/
TEST_F(rolledUp, empty) {

    ropeCheck("");

}

TEST_F(rolledUp, simpleTrue) {

    ropeCheck("news");

}

TEST_F(rolledUp, overStartTrue) {

    ropeCheck("nsewsssnnnns");

}

TEST_F(rolledUp, stressTrue) {
    std::string s(100000, 's');
    std::string w(100000, 'w');
    std::string e(100000, 'e');
    std::string n(100000, 'n');

    ropeCheck(s + n + e + w);

}

TEST_F(notRolledUp, simpleFalse) {

    ropeCheck("nswees");

}

TEST_F(notRolledUp, endStartFalse) {

    ropeCheck("nesw");

}

TEST_F(notRolledUp, stressFalse) {
    std::string s(100000, 's');
    std::string w(100000, 'w');
    std::string e(100000, 'e');
    std::string n(100000, 'n');

    ropeCheck(s + n + 'w' + 's' + e + w);

}

TEST_F(invalid, simpleInvalid) {

    ropeCheck("bob");

}

TEST_F(invalid, simpleInvalid1) {

    ropeCheck(" ");

}

TEST_F(invalid, simpleInvalid2) {

    ropeCheck("n w");

}

TEST_F(invalid, simpleInvalid3) {

    ropeCheck("n w ");

}

TEST_F(invalid, simpleInvalid4) {

    ropeCheck("n\ts");

}

TEST_F(invalid, simpleInvalid5) {

    ropeCheck("news ");

}

TEST_F(invalid, simpleInvalid6) {

    ropeCheck(" news");

}

TEST_F(invalid, simpleInvalid7) {

    ropeCheck("nwesnwensewnwensewnesnwesnb");

}

TEST_F(invalid, simpleInvalid8) {

    ropeCheck("NEWS");

}
