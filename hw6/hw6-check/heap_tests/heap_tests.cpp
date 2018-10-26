#include <gtest/gtest.h>
#include <random_generator.h>
#include "../../MinHeap.h"

#include <string>
#include <vector>
#include <algorithm>
#include <utility>

#include <cassert>

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

class MinHeapSort : public ::testing::Test {
protected:
  MinHeap<int>* mh;
  size_t array_size;

  void SetUp(size_t array_size) {
    this->array_size = array_size;
  }

  void runRange(size_t begin, size_t end, size_t skip = 1) {
    assert(begin >= 2 && begin < end);

    for (size_t i = begin; i < end; i += skip) {
      cout << "Running with k=" << i << endl;
      run(i);
    }
  }

  void run(int d) {
    mh = new MinHeap<int>(d);
    vector<int> vec = makeRandomNumberVector(array_size, 0, 2147483646, 12345, true);
    vector<int> vec2 = makeRandomNumberVector(array_size, 0, 2147483646, 12345, false);

    vector<pair<int, int>> res;

    for (size_t i = 0; i < vec.size(); i++) {
      mh->add(vec[i], vec2[i]);
      res.push_back(make_pair(vec[i], vec2[i]));
    }

    // https://stackoverflow.com/a/279878
    std::sort(res.begin(), res.end(), [](const std::pair<int,int> &left, const std::pair<int,int> &right) {
      return left.second < right.second;
    });

    for (size_t i = 0; i < res.size(); i++) {
      EXPECT_EQ(mh->peek(), res[i].first);
      mh->remove();
    }

    EXPECT_TRUE(mh->isEmpty());

    delete mh;
  }
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

TEST_F (MinHeapNum, TwoAryAdd) {
  SetUp(2);
  mh->add(420, 1);
}

TEST_F (MinHeapNum, ThreeAryAdd) {
  SetUp(3);
  mh->add(420, 1);
}

TEST_F (MinHeapNum, peek) {
  SetUp(2);
  mh->add(420, 1);
  EXPECT_EQ(mh->peek(), 420);
}

TEST_F (MinHeapNum, peekTwoItems) {
  SetUp(2);
  mh->add(111, 1);
  mh->add(120, 2);
  EXPECT_EQ(mh->peek(), 111);
}

TEST_F (MinHeapNum, peekFiveItems) {
  SetUp(2);
  mh->add(100, 2);
  mh->add(400, 7);
  mh->add(300, 3);
  mh->add(500, 10);
  mh->add(1, 1);

  EXPECT_EQ(mh->peek(), 1);
  mh->remove();

  EXPECT_EQ(mh->peek(), 100);
  mh->remove();

  EXPECT_EQ(mh->peek(), 300);
  mh->remove();

  EXPECT_EQ(mh->peek(), 400);
  mh->remove();

  EXPECT_EQ(mh->peek(), 500);
  mh->remove();

  EXPECT_TRUE(mh->isEmpty());
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

TEST_F (MinHeapNum, EmptyRemove) {
  SetUp(2);
  try {
    mh->remove();
  } catch (exception& e) {
    return;
  }
  FAIL();
}

TEST_F (MinHeapNum, EmptyPeek) {
  SetUp(2);
  try {
    mh->peek();
  } catch (exception& e) {
    return;
  }
  FAIL();
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

/* Perform heap sort with 100 elements and k-ary heaps in steps of 1 */
TEST_F (MinHeapSort, HeapSort100) {
  SetUp(100);
  runRange(2, 100);
}

/* Perform heap sort with 1000 elements and k-ary heaps in steps of 3 */
TEST_F (MinHeapSort, HeapSort1000) {
  SetUp(1000);
  runRange(2, 100, 3);
}

/* Perform  100 add operations on a d-ary heap for 2 <= d <= 100 */
TEST (MinHeapNary, DAryAdd) {
  MinHeap<int>* mh;
  for (int i = 2; i <= 100; i++) {
    mh = new MinHeap<int>(i);
    mh->add(i, i);
    delete mh;
  }
}

/* Perform 100 add and peek operations on a d-ary heap for 2 <= d <= 100 */
TEST (MinHeapNary, DAryPeek) {
  MinHeap<int>* mh;
  for (int i = 2; i <= 100; i++) {
    mh = new MinHeap<int>(i);
    for (int b = i; b < 20*i; b++) {
      mh->add(b, 20*i - b);
      EXPECT_EQ(mh->peek(), b);
    }
    delete mh;
  }
}
