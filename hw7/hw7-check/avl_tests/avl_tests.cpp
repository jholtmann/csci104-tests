#include <gtest/gtest.h>
#include <random_generator.h>
#include "../../avlbst.h"

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <sstream>

#include <cassert>

using namespace std;

void waitForEnter() {
  cout << "> Press Enter to Continue";
  cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
}

/*** Test Fixtures ***/
template<typename Key, typename Value>
class AVLTest : public ::testing::Test {
protected:
  AVLTree<Key, Value>* avl;
  vector<pair<Key, Value>> pairs;

  virtual void SetUp() {
	   avl = new AVLTree<Key, Value>();
  }

  virtual void TearDown() {
	   delete avl;
  }

  const pair<Key, Value>& insert(pair<Key, Value> p) {
    pairs.push_back(p);
    avl->insert(pairs.back());

    return pairs.back();
  }

  void remove(const pair<Key, Value> &p) {
    try {
      avl->remove(p.first);
      pairs.erase(find(pairs.begin(), pairs.end(), p));
    } catch (exception &e) {
      cerr << "Expected value not found. This should only be possible if there ";
      cerr << "is a mistake in the tests. Please contact Jonathan Holtmann." << endl;
      FAIL();
    }
  }

  void check(const pair<Key, Value> &p) const {
    auto avl_it = avl->find(p.first);
    auto pairs_it = find(pairs.begin(), pairs.end(), p);

    ASSERT_TRUE(avl_it != avl->end());
    if (pairs_it == pairs.end()) {
      cerr << "ERROR" << endl;
      return;
    }

    ASSERT_EQ(avl_it->second, pairs_it->second);

    ASSERT_TRUE(avl->isBalanced());
  }

  void checkRemove(const pair<Key, Value> p) {
    remove(p);
    auto it = avl->find(p.first);
    ASSERT_TRUE(it == avl->end());
    ASSERT_TRUE(avl->isBalanced());
  }

  void checkInsert(pair<Key, Value> p) {
    check(insert(p));
  }

  void clear() {
    avl->clear();
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

  streambuf* beginCapture(stringstream &ss) {
    streambuf *sbuf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    return sbuf;
  }

  void endCapture(streambuf* sbuf) {
    cout.rdbuf(sbuf);
  }

  // Returns reference to pair if found in vector, otherwise throws exception
  string printTree(vector<pair<Key, Value>> vec) {
    AVLTree<Key, Value> avl;
    for (auto &p : vec) {
      avl.insert(p);
    }

    stringstream output;
    streambuf* buf = beginCapture(output);

    avl.print();

    endCapture(buf);

    return output.str();
  }

  string treeToString(AVLTree<Key, Value>* avl) {
    stringstream output;
    streambuf* buf = beginCapture(output);

    avl->print();

    endCapture(buf);

    return output.str();
  }

  void compareTrees(vector<pair<Key, Value>> vec, AVLTree<Key, Value>* avl) {
    string expected = printTree(vec);
    string result = treeToString(avl);

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

class AVLTestInt : public AVLTest<int, int> {
protected:
  const pair<int, int>& insert(int i) {
    return AVLTest<int, int>::insert(make_pair(i, i));
  }

  void checkInsert(int i) {
    AVLTest<int, int>::checkInsert(make_pair(i, i));
  }

  string printTree(vector<int> vec) {
    vector<pair<int, int>> vec2;
    for (int &i : vec) {
      vec2.push_back(make_pair(i, i));
    }
    return AVLTest<int, int>::printTree(vec2);
  }

  void massInsert(vector<int> vec) {
    for (auto &i : vec) {
      checkInsert(i);
    }
  }

  void compareTrees(vector<int> vec, AVLTree<int, int>* avl) {
    vector<pair<int, int>> vec2;
    for (int &i : vec) {
      vec2.push_back(make_pair(i, i));
    }
    AVLTest<int, int>::compareTrees(vec2, avl);
  }
};

TEST_F(AVLTestInt, CreateDestroy) {}

TEST_F(AVLTestInt, AddSingle) {
  checkInsert(1);
}

TEST_F(AVLTestInt, AddTwo) {
  checkInsert(1);
  checkInsert(2);

  string expected = printTree({1, 2});
  ASSERT_EQ(treeToString(avl), expected);
}

TEST_F(AVLTestInt, AddDuplicateKeys) {
  AVLTest<int, int>::checkInsert(make_pair(1, 1));
  AVLTest<int, int>::checkInsert(make_pair(1, 2));

  string expected = AVLTest<int, int>::printTree({make_pair(1, 2)});
  ASSERT_EQ(treeToString(avl), expected);
}

TEST_F(AVLTestInt, ZigZigOne) {
  checkInsert(10);
  checkInsert(9);
  checkInsert(8);


  string expected = printTree({9, 8, 10});
  ASSERT_EQ(treeToString(avl), expected);
}

TEST_F(AVLTestInt, ZigZigLarge) {
  for (int i = 50; i >= 0; i--) {
    checkInsert(i);
  }

  avl->print();
  waitForEnter();
}

TEST_F(AVLTestInt, ZigZagOne) {
  checkInsert(10);
  checkInsert(8);
  checkInsert(9);

  string expected = printTree({9, 8, 10});
  ASSERT_EQ(treeToString(avl), expected);
}

TEST_F(AVLTestInt, ZigZigRemoveUnbalanced) {
  massInsert({10, 5, 15, 1});

  checkRemove(findByKey(15));

  for (auto &p : pairs) {
    check(p);
  }

  ASSERT_TRUE(avl->isBalanced());

  string expected = printTree({5, 1, 10});
  ASSERT_EQ(treeToString(avl), expected);
}

TEST_F(AVLTestInt, ZigZigRemoveTwoUnbalanced) {
  massInsert({10, 5, 15, 1, 7});

  checkRemove(findByKey(15));

  for (auto &p : pairs) {
    check(p);
  }

  ASSERT_TRUE(avl->isBalanced());

  string expected = printTree({5, 1, 10, 7});
  ASSERT_EQ(treeToString(avl), expected);
}

TEST_F(AVLTestInt, SingleChildRemoveBalanced) {
  massInsert({10, 5, 15, 1, 7, 16});

  checkRemove(findByKey(15));

  for (auto &p : pairs) {
    check(p);
  }

  ASSERT_TRUE(avl->isBalanced());
  compareTrees({10, 5, 16, 1, 7}, avl);
}

TEST_F(AVLTestInt, TwoChildRemoveUnbalanced) {
  massInsert({10, 5, 15, 1, 7, 12, 16, 17});

  checkRemove(findByKey(15));

  // for (auto &p : pairs) {
  //   check(p);
  // }

  compareTrees({10, 5, 16, 1, 7, 12, 17}, avl);
}
