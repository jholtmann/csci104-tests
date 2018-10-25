#include "gtest/gtest.h"

#include "../MinHeap.h"

/*** Test Fixture ***/
// Base class; no defaults (as of now)
class MinHeapTest : public ::testing::Test {
protected:
};

class MinHeapNum : public MinHeapTest {
protected:
    MinHeap<int> mh;
};

class MinHeapString : public MinHeapTest {
protected:
    MinHeap<std::string> mh(2);
};

/*** Test Definitions ***/
// Simple tests (basic functionality)
TEST_F (MinHeapNum, add) {
    mh.add(420, 1);
}

TEST_F (MinHeapNum, peek) {
    mh.add(420, 1);
    EXPECT_EQ(mh.peek(), 420);
}

TEST_F (MinHeapNum, rm) {
    mh.add(420, 1);
    mh.add(911, 2);
    mh.remove();

    EXPECT_EQ(mh.peek(), 911);
}

TEST_F (MinHeapNum, empty) {
    EXPECT_TRUE(mh.isEmpty());

    mh.add(420, 1);
    mh.remove();

    EXPECT_TRUE(mh.isEmpty());
}

TEST_F (MinHeapString, add) {
    mh.add("bob", 1);
}

TEST_F (MinHeapString, peek) {
    mh.add("bob", 1);
    EXPECT_EQ(mh.peek(), "bob");
}

TEST_F (MinHeapString, rm) {
    mh.add("bob", 1);
    mh.add("jim", 2);
    mh.remove();

    EXPECT_EQ(mh.peek(), "jim");
}

TEST_F (MinHeapString, empty) {
    EXPECT_TRUE(mh.isEmpty());

    mh.add("tim", 1);
    mh.remove();

    EXPECT_TRUE(mh.isEmpty());
}
