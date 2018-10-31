#include <gtest/gtest.h>
#include <random_generator.h>
#include "../../MinHeap.h"

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>

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

class MinHeapNumParam : public MinHeapNum, public ::testing::WithParamInterface<int> {
protected:
};

class MinHeapSort : public ::testing::TestWithParam<int> {
protected:
  MinHeap<int>* mh;
  size_t array_size;

  void SetUp(size_t array_size) {
	this->array_size = array_size;
  }

  void sortTest() {
	mh = new MinHeap<int>(GetParam());
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

/*** Value Paramaterized Tests ***/
// Test MinHeapNumParam tests with a d-value from 2-20
INSTANTIATE_TEST_CASE_P(MinHeapNumMultiSmall, MinHeapNumParam, ::testing::Range(2, 21));

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


TEST_P (MinHeapNumParam, peekTwoItems) {
  SetUp(GetParam());
  mh->add(111, 1);
  mh->add(120, 2);
  EXPECT_EQ(mh->peek(), 111);
}

TEST_P (MinHeapNumParam, peekFiveItems) {
  SetUp(GetParam());
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

TEST_P (MinHeapNumParam, PeekHundredItems) {
  SetUp(GetParam());
for (int b = 0; b < 100; b++) {
  mh->add(b, 100 - b);
  EXPECT_EQ(mh->peek(), b);
}
}

TEST_P (MinHeapNumParam, FillToTheBrimEmpty) {
  SetUp(GetParam());
  srand(1);
  for (int i = 0; i < 10000; i++) {
	mh->add(i, 10000 - i);
  }
  for (int i = 0; i < 10000; i++) {
  	mh->remove();
  }
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


INSTANTIATE_TEST_CASE_P(MinHeapSortVaryingD, MinHeapSort, ::testing::Range(2, 104));

/* Perform heap sort with 100 elements and k-ary heaps in steps of 1 */
TEST_P (MinHeapSort, HeapSort100) {
  SetUp(100);
  sortTest();
}

/* Perform heap sort with 10000 elements and k-ary heaps in steps of 3 */
TEST_P (MinHeapSort, HeapSort543) {
  SetUp(543);
  sortTest();
}

/* Perform heap sort with 1000 elements and k-ary heaps in steps of 3 */
TEST_P (MinHeapSort, HeapSort1000) {
  SetUp(1000);
  sortTest();
}
