#include "gtest/gtest.h"

#include "../msort.h"

#include "utils/runtime_evaluator.h"
#include "utils/random_generator.h"

#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

struct AlphaStrComp {
  bool operator() (const string& lhs, const string& rhs)
  { // Uses string's built in operator<
    // to do lexicographic (alphabetical) comparison
    return (lhs < rhs);
  }
};

struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by size;
    // Breaks ties by lexicographic comparison
    return (   (lhs.size() < rhs.size())
            || (lhs.size() == rhs.size() && lhs < rhs));
  }
};

struct NumComp {
  bool operator()(const double& lhs, const double& rhs)
  {
    return (lhs < rhs);
  }
};

struct RevNumComp {
  bool operator()(const double& lhs, const double& rhs)
  {
    return (lhs > rhs);
  }
};

struct NumCompRuntimeKTwo {
    chrono::microseconds operator()(uint64_t n, int seed) const {
			BenchmarkTimer tmr(false);
			vector<int> contents = makeRandomNumberVector(n, 0, 2147483646, seed, true);
      NumComp comp;

			tmr.start();
			mergeSort(contents, 2, comp);
			tmr.stop();

			return tmr.getTime();
    }
};

struct NumCompRuntimeKN {
    chrono::microseconds operator()(uint64_t n, int seed) const {
			BenchmarkTimer tmr(false);
			vector<int> contents = makeRandomNumberVector(n, 0, 2147483646, seed, true);
      NumComp comp;

			tmr.start();
			mergeSort(contents, n, comp);
			tmr.stop();

			return tmr.getTime();
    }
};

TEST(MergeNumeric, TenElementTwoK) {
  vector<int> vec = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  vector<int> sortedVec = vec;

  std::sort(vec.begin(), vec.end(), NumComp());

  NumComp comp;

  mergeSort(sortedVec, 2, comp);

  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_EQ(sortedVec[i], vec[i]);
  }
}

TEST(MergeNumericReverse, TenElementTwoK) {
  vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
  vector<int> sortedVec = vec;

  std::sort(vec.begin(), vec.end(), RevNumComp());

  RevNumComp comp;

  mergeSort(sortedVec, 2, comp);

  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_EQ(sortedVec[i], vec[i]);
  }
}

TEST(MergeNumeric, TenElementAllK) {
  vector<int> vec = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  vector<int> sortedVec = vec;

  std::sort(vec.begin(), vec.end(), NumComp());

  NumComp comp;

  for (int k = 2; k <= 10; k++) {
    mergeSort(sortedVec, k, comp);
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(sortedVec[i], vec[i]);
    }
  }
}

TEST(MergeNumeric, TenElementAlreadySorted) {
  vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
  vector<int> sortedVec = vec;

  NumComp comp;

  for (int k = 2; k <= 10; k++) {
    mergeSort(sortedVec, k, comp);
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(sortedVec[i], vec[i]);
    }
  }
}

TEST(MergeNumeric, TenElementFiveEqual) {
  vector<int> vec = {5,5,5,5,5,1,1,1,1,1};
  vector<int> sortedVec = vec;

  std::sort(vec.begin(), vec.end(), NumComp());

  NumComp comp;

  for (int k = 2; k <= 10; k++) {
    mergeSort(sortedVec, k, comp);
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(sortedVec[i], vec[i]);
    }
  }
}

TEST(MergeAlphaStrComp, TwoElementSort) {
  vector<string> vec = {"b", "a"};
  vector<string> sortedVec = vec;

  std::sort(vec.begin(), vec.end(), AlphaStrComp());

  AlphaStrComp alph;

  mergeSort(sortedVec, 2, alph);

  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_EQ(sortedVec[i], vec[i]);
  }
}

TEST(MergeAlphaStrComp, SevenElementMixedK) {
  vector<string> vec = {"xyz", "def", "eee", "abc", "zzz", "aaa", "aab"};
  vector<string> sortedVec = vec;

  std::sort(vec.begin(), vec.end(), AlphaStrComp());

  AlphaStrComp alph;

  for (int k = 2; k <= 7; k++) {
    mergeSort(sortedVec, k, alph);
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(sortedVec[i], vec[i]);
    }
  }
}

TEST(MergeLengthStrComp, TwoElementSort) {
  vector<string> vec = {"b", "a", "bbb", "ab", "123fd", "hello world"};
  vector<string> sortedVec = vec;

  std::sort(vec.begin(), vec.end(), LengthStrComp());

  LengthStrComp alph;

  mergeSort(sortedVec, 5, alph);

  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_EQ(sortedVec[i], vec[i]);
  }
}

TEST(MergeNumericStress, TenThousandElement) {
  srand(12345);
  vector<int> vec;
  for (int i = 0; i < 10000; i++) {
    vec.push_back(rand());
  }
  vector<int> sortedVec = vec;

  std::sort(vec.begin(), vec.end(), NumComp());

  NumComp comp;

  for (int k = 2; k <= 10000; k+=998) {
    cout << "Sorting with k=" << k << endl;
    mergeSort(sortedVec, k, comp);
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(sortedVec[i], vec[i]);
    }
  }
}

TEST(MergeNumericStress, HundredThousandElement) {
  srand(999999);
  vector<int> vec;
  for (int i = 0; i < 100000; i++) {
    vec.push_back(rand());
  }
  vector<int> sortedVec = vec;

  std::sort(vec.begin(), vec.end(), NumComp());

  NumComp comp;

  for (int k = 2; k <= 100000; k+=9998) {
    cout << "Sorting with k=" << k << endl;
    mergeSort(sortedVec, k, comp);
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(sortedVec[i], vec[i]);
    }
  }
}

TEST(MergeRuntime, NumCompRuntimeKTwo) {
	RuntimeEvaluator rntm("mergeSort", 1, 18, 3, NumCompRuntimeKTwo());
  rntm.setCorrelationThreshold(2);
	rntm.evaluate();
	ASSERT_TRUE(rntm.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEAR));
}

TEST(MergeRuntime, NumCompRuntimeKN) {
	RuntimeEvaluator rntm("mergeSort", 1, 18, 3, NumCompRuntimeKN());
  rntm.setCorrelationThreshold(1.25);
	rntm.evaluate();
	ASSERT_TRUE(rntm.meetsComplexity(RuntimeEvaluator::TimeComplexity::QUADRATIC));
}
