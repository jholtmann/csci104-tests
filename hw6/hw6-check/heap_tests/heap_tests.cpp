#include <gtest/gtest.h>

#include "../../MinHeap.h"

#include <string>

using namespace std;

/*** Test Fixtures ***/
class MinHeapNum : public ::testing::Test {
protected:
  MinHeap<int>* mh;

  void SetUp(int d) {
    mh = new MinHeap<int>(d);
  }

  virtual void TearDown() {
    delete mh;
  }
};

class MinHeapNumParam : public MinHeapNum, public ::testing::WithParamInterface<const int> {
protected:
};


class MinHeapString : public ::testing::Test {
protected:
  MinHeap<string>* mh;

  void SetUp(int d) {
    mh = new MinHeap<string>(d);
  }

  virtual void TearDown() {
    delete mh;
  }
};

/*** Basic Tests ***/
TEST_F (MinHeapNum, add) {
  SetUp(2);
  mh->add(420, 1);
}

TEST_F (MinHeapNum, peek) {
  SetUp(2);
  mh->add(420, 1);
  EXPECT_EQ(mh->peek(), 420);
}

TEST_F (MinHeapNum, rm) {
  SetUp(2);
  mh->add(420, 1);
  mh->add(911, 2);
  mh->remove();

  EXPECT_EQ(mh->peek(), 911);
}

TEST_F (MinHeapNum, empty) {
  SetUp(2);
  EXPECT_TRUE(mh->isEmpty());

  mh->add(420, 1);
  mh->remove();

  EXPECT_TRUE(mh->isEmpty());
}

TEST_F (MinHeapString, add) {
  SetUp(2);
  mh->add("bob", 1);
}

TEST_F (MinHeapString, peek) {
  SetUp(2);
  mh->add("bob", 1);
  EXPECT_EQ(mh->peek(), "bob");
}

TEST_F (MinHeapString, rm) {
  SetUp(2);
  mh->add("bob", 1);
  mh->add("jim", 2);
  mh->remove();

  EXPECT_EQ(mh->peek(), "jim");
}

TEST_F (MinHeapString, empty) {
  SetUp(2);
  EXPECT_TRUE(mh->isEmpty());

  mh->add("tim", 1);
  mh->remove();

  EXPECT_TRUE(mh->isEmpty());
}

/*** Value Paramaterized Tests ***/
// Test MinHeapNumParam tests with a d-value from 2-20
INSTANTIATE_TEST_CASE_P(MinHeapNumMultiSmall, MinHeapNumParam, ::testing::Range(2, 21))

TEST_P (MinHeapNumParam, add) {
  SetUp(GetParam());
  mh->add(420, 1);
}

TEST_P (MinHeapNumParam, peek) {
  SetUp(GetParam());
  mh->add(420, 1);
  EXPECT_EQ(mh->peek(), 420);
}

TEST_P (MinHeapNumParam, rm) {
  SetUp(GetParam());
  mh->add(420, 1);
  mh->add(911, 2);
  mh->remove();

  EXPECT_EQ(mh->peek(), 911);
}

TEST_P (MinHeapNumParam, empty) {
  SetUp(GetParam());
  EXPECT_TRUE(mh->isEmpty());

  mh->add(420, 1);
  mh->remove();

  EXPECT_TRUE(mh->isEmpty());
}


