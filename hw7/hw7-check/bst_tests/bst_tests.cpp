#include <gtest/gtest.h>
#include <random_generator.h>
#include "../../bst.h"

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>

#include <cassert>

using namespace std;

/*** Test Fixtures ***/
template<typename Key, typename Value>
class BSTTest : public ::testing::Test {
protected:
  BinarySearchTree<Key, Value>* bst;

  vector<pair<Key, Value>> pairs;

  void SetUp() {
	   bst = new BinarySearchTree<Key, Value>();
  }

  virtual void TearDown() {
	   delete bst;
  }

  const pair<Key, Value>& insert(pair<Key, Value> p) {
    pairs.push_back(p);
    bst->insert(pairs.back());
    return pairs.back();
  }

  void remove(const pair<Key, Value> &p) {
    try {
      bst->remove(p.first);
      pairs.erase(find(pairs.begin(), pairs.end(), p));
    } catch (exception &e) {
      cerr << "Expected value not found. This should only be possible if there ";
      cerr << "is a mistake in the tests. Please contact Jonathan Holtmann." << endl;
      FAIL();
    }
  }

  void clear() {
    bst->clear();
    pairs.clear();
  }

  // Returns reference to pair if found in vector, otherwise throws exception
  const pair<Key, Value>& findByKey(Key k) {
    for (auto &p : pairs)  {
      if (p.first == k) {
        return p;
      }
    }
    throw exception();
  }

  // Returns reference to pair if found in vector, otherwise throws exception
  const pair<Key, Value>& findByValue(Value v) {
    for (auto &p : pairs)  {
      if (p.second == v) {
        return p;
      }
    }
    throw exception();
  }

  // Returns reference to pair if found in vector, otherwise throws exception
  const pair<Key, Value>& findByPair(pair<Key, Value> p) {
    auto it = find(pairs.begin(), pairs.end(), p);
    if (it != pairs.end()) {
      return *it;
    }
  }

  void check(const pair<Key,Value> &p) const {
    ASSERT_TRUE(bst->find(p.first) != bst->end());
  }

  void checkRemove(const pair<Key,Value> &p) {
    remove(p);
    ASSERT_TRUE(bst->find(p.first) == bst->end());
  }
};

// Test class for int int BST
class BSTTestIntStr : public BSTTest<int, string> {};

// Test fixture for int int BST
class BSTTestInt : public BSTTest<int, int> {
protected:
  const pair<int, int>& insert(int i) {
    pair<int, int> p(i, i);
    pairs.push_back(p);
    bst->insert(p);
    return pairs.back();
  }
};

TEST_F(BSTTestIntStr, CreateDestroy) {}

TEST_F(BSTTestIntStr, AddSingleItem) {
  check(insert(make_pair(10, "aaa")));
}

TEST_F(BSTTestIntStr, SingleItemBalanced) {
  check(insert(make_pair(10, "aaa")));
  ASSERT_TRUE(bst->isBalanced());
}

TEST_F(BSTTestIntStr, SingleItemRemove) {
  check(insert(make_pair(10, "aaa")));

  remove(findByKey(10));

  ASSERT_TRUE(bst->find(10) == bst->end());
}

TEST_F(BSTTestIntStr, SingleItemClear) {
  check(insert(make_pair(10, "aaa")));
  clear();

  ASSERT_TRUE(bst->find(10) == bst->end());
}

TEST_F(BSTTestIntStr, AddFiveItems) {
  check(insert(make_pair(20, "bbb")));
  check(insert(make_pair(10, "aaa")));
  check(insert(make_pair(30, "ccc")));
  check(insert(make_pair(9, "abc")));
  check(insert(make_pair(11, "def")));
}

TEST_F(BSTTestInt, AddFiveRemoveFive) {
  check(insert(3));
  check(insert(2));
  check(insert(1));
  check(insert(4));
  check(insert(5));

  for (int i = 5; i > 0; i--) {
    checkRemove(findByKey(i));
  }
}
