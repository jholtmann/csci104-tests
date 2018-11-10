#include <gtest/gtest.h>
#include <random_generator.h>
#include "../../rotateBST.h"

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>

#include <cassert>

using namespace std;

/* Test fixtures */
template<typename Key, typename Value>
class RotateBSTTest : public ::testing::Test {
protected:
  rotateBST<Key, Value>* rst;
  vector<pair<Key, Value>> pairs;

  virtual void SetUp() {
	   rst = new rotateBST<Key, Value>();
  }

  virtual void TearDown() {
	   delete rst;
  }
};

class RotateInt : public RotateBSTTest<int, int> {};

// Test fixture for BSTSort
class SameKeys : public ::testing::TestWithParam<int>  {
protected:
  rotateBST<int, int>* rst;
  rotateBST<int, int>* rst2;
  vector<pair<int, int>> pairs;

  void SetUp() {
    rst = new rotateBST<int, int>();
    rst2 = new rotateBST<int, int>();
  }

  void runTest(size_t array_size) {
    vector<int> vec = makeRandomNumberVector(array_size, 0, 2147483646, 1, false);
    vector<int> vec2 = makeRandomNumberVector(array_size, 0, 2147483646, 1, true);

  	for (size_t i = 0; i < vec.size(); i++) {
      pairs.push_back(make_pair(vec[i], vec2[i]));
  	  rst->insert(pairs.back());
  	}

    srand(1);
    random_shuffle(pairs.begin(), pairs.end());

    for (auto &p : pairs) {
      rst2->insert(p);
    }

    ASSERT_TRUE(rst->sameKeys(*rst2));
    ASSERT_TRUE(rst2->sameKeys(*rst));
  }

  void TearDown() {
    delete rst;
    delete rst2;
  }
};

TEST_F(RotateInt, Create) {}

INSTANTIATE_TEST_CASE_P(RotateBSTTestSameKeys, SameKeys, ::testing::Range(10, 10010, 200));

TEST_P(SameKeys, SameKeysMass) {
  runTest(GetParam());
}

TEST_P(SameKeys, SameKeysTransform) {
  cout << "Running transform with array size: " << GetParam() << endl;

  runTest(GetParam());

  rst->transform(*rst2);

  auto it = rst->begin();
  auto it2 = rst2->begin();

  while (it != rst->end() && it2 != rst2->end()) {
    ASSERT_EQ(it->first, it2->first);
    ++it;
    ++it2;
  }
}
