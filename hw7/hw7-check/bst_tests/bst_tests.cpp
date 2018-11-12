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

void waitForEnter() {
  cout << "> Press Enter to Continue";
  cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
}

/*** Test Fixtures ***/
template<typename Key, typename Value>
class BSTTest : public ::testing::Test {
protected:
  BinarySearchTree<Key, Value>* bst;
  vector<pair<Key, Value>> pairs;

  virtual void SetUp() {
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

  void check(const pair<Key, Value> &p) const {
    ASSERT_TRUE(bst->find(p.first) != bst->end());
  }

  void checkRemove(const pair<Key, Value> p) {
    remove(p);
    auto it = bst->find(p.first);
    ASSERT_TRUE(it == bst->end());
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

// Test fixture for BSTSort
class BSTSort : public ::testing::TestWithParam<int>  {
protected:
  BinarySearchTree<int, int>* bst;
  vector<pair<int, int>> pairs;

  void runTest(size_t array_size, bool remove = false) {
    bst = new BinarySearchTree<int, int>();

    // cout << "Sorting array of size: " << array_size << endl;

    vector<int> vec = makeRandomNumberVector(array_size, 0, 2147483646, 1, false);
    vector<int> vec2 = makeRandomNumberVector(array_size, 0, 2147483646, 1, true);

  	for (size_t i = 0; i < vec.size(); i++) {
      pairs.push_back(make_pair(vec[i], vec2[i]));
  	  bst->insert(pairs.back());
  	}

    std::sort(pairs.begin(), pairs.end());

    if (!remove) {
      size_t i = 0;
      for (auto &p : *bst) {
        ASSERT_EQ(p.first, pairs[i].first);
        ASSERT_EQ(p.second, pairs[i].second);
        i++;
      }
    } else {
      for (auto &p : pairs) {
        auto first = bst->begin();

        ASSERT_EQ(first->first, p.first);
        ASSERT_EQ(first->second, p.second);
        bst->remove(p.first);
      }
    }

    delete bst;
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

TEST_F(BSTTestInt, DuplicateKeys) {
  check(insert(20));
  check(insert(20));
}

TEST_F(BSTTestInt, AddFiveItemsIterate) {
  insert(20);
  insert(10);
  insert(30);
  insert(9);
  insert(11);

  sort(pairs.begin(), pairs.end());

  size_t i = 0;
  for (auto key : *bst) {
    ASSERT_EQ(key, pairs[i]);
    i++;
  }
}

TEST_F(BSTTestInt, AddFiveRemoveRoot) {
  check(insert(3));
  check(insert(2));
  check(insert(1));
  check(insert(4));
  check(insert(5));

  checkRemove(findByKey(3));

  check(findByKey(2));
  check(findByKey(1));
  check(findByKey(4));
  check(findByKey(5));
}

TEST_F(BSTTestInt, AddRemoveFive) {
  check(insert(3));
  check(insert(2));
  check(insert(1));
  check(insert(4));
  check(insert(5));

  for (int i = 5; i > 0; i--) {
    checkRemove(findByKey(i));
  }
}

TEST_F(BSTTestInt, DirectPredecessor) {
  check(insert(10));
  check(insert(8));
  check(insert(20));
  check(insert(15));
  check(insert(13));
  check(insert(21));

  bst->print();

  cout << "Removing node with key 20" << endl;
  checkRemove(findByKey(20));

  for (auto &p : pairs) {
    check(p);
  }

  bst->print();
  waitForEnter();
}

TEST_F(BSTTestInt, IndirectPredecessorLeftChild) {
  check(insert(1));
  check(insert(0));
  check(insert(10));
  check(insert(2));
  check(insert(8));
  check(insert(3));
  check(insert(11));

  bst->print();

  cout << "Removing node with key 10" << endl;
  checkRemove(findByKey(10));

  for (auto &p : pairs) {
    check(p);
  }

  bst->print();
  waitForEnter();
}

INSTANTIATE_TEST_CASE_P(BSTSortNItems, BSTSort, ::testing::Range(10, 10010, 100));

TEST_P(BSTSort, StressSort) {
  runTest(GetParam());
}

TEST_P(BSTSort, StressSortRemove) {
  runTest(GetParam(), true);
}
