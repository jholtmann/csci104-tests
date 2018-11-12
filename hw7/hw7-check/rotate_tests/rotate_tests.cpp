#include <gtest/gtest.h>
#include <random_generator.h>
#include "../../rotateBST.h"

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <climits>
#include <sstream>

#include <cassert>

using namespace std;

void waitForEnter() {
  cout << "> Press Enter to Continue";
  cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
}

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
class RotateMass : public ::testing::TestWithParam<int>  {
protected:
  rotateBST<int, int>* rst;
  rotateBST<int, int>* rst2;
  vector<pair<int, int>> pairs;

  void SetUp() {
    rst = new rotateBST<int, int>();
    rst2 = new rotateBST<int, int>();
  }

  void runTest(size_t array_size, size_t seed) {
    vector<int> vec = makeRandomNumberVector(array_size, 0, 2147483646, seed, false);
    vector<int> vec2 = makeRandomNumberVector(array_size, 0, 2147483646, seed, true);

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

  virtual void TearDown() {
    delete rst;
    delete rst2;
  }

  streambuf* beginCapture(stringstream &ss) {
    streambuf *sbuf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    return sbuf;
  }

  void endCapture(streambuf* sbuf) {
    cout.rdbuf(sbuf);
  }

  string treeToString(BinarySearchTree<int, int>* bst) {
    stringstream output;
    streambuf* buf = beginCapture(output);

    bst->print();

    endCapture(buf);

    return output.str();
  }

  void compareTrees(BinarySearchTree<int, int>* bst1, BinarySearchTree<int, int>* bst2) {
    string expected = treeToString(bst1);
    string result = treeToString(bst2);

    // Hack to keep google test from printign expected/got output
    // If there is time, this can be done better with a custom TestEventListener
    if (result != expected) {
      EXPECT_TRUE(false);
    }

    if (::testing::Test::HasFailure()) {
      cout << "EXPECTED:" << endl;
      cout << expected;
      cout << endl << "GOT: " << endl;
      cout << result << endl;
    }
  }
};

class RotateIntTransform : public RotateMass {};

TEST_F(RotateInt, Create) {}

INSTANTIATE_TEST_CASE_P(Transform, RotateIntTransform, ::testing::Range(5, 145, 5));

TEST_P(RotateIntTransform, LimitedTransform) {
  runTest(GetParam(), 12345);

  rst->transform(*rst2);

  ASSERT_TRUE(rst->sameKeys(*rst2));
  ASSERT_TRUE(rst2->sameKeys(*rst));

  compareTrees(rst, rst2);
}

INSTANTIATE_TEST_CASE_P(RotateBSTTestSameKeys, RotateMass, ::testing::Range(10, 10000, 101));

TEST_P(RotateMass, MassSameKeys) {
  runTest(GetParam(), 12345);
}

TEST_P(RotateMass, MassTransform) {
  runTest(GetParam(), 12345);

  rst->transform(*rst2);

  auto it = rst->begin();
  auto it2 = rst2->begin();

  while (it != rst->end() && it2 != rst2->end()) {
    ASSERT_EQ(it->first, it2->first);
    ++it;
    ++it2;
  }

  compareTrees(rst, rst2);
}
