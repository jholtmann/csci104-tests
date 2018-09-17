#include <gtest/gtest.h>
#include <selection_sort.h>
#include <selection_sort_utils.h>
#include <misc_utils.h>
#include <map>
#include <chrono>
#include <runtime_evaluator.h>
#include <random_generator.h>
#include <algorithm>

/* 	AUTHOR: JONATHAN HOLTMANN
		EMAIL: holtmann@usc.edu
		DESCIPTION: The following contains extra test cases for the CSCI 104
								homework assignment nr. 2
*/

struct findMinN {
    std::chrono::microseconds operator()(uint64_t n, int seed) const {
			BenchmarkTimer tmr(false);

			std::vector<int> contents = makeRandomNumberVector(n, 0, 2147483646, seed, false);
			Item *list = makeList(contents);

			tmr.start();
			findMin(list);
			tmr.stop();

			deleteList(list);

			return tmr.getTime();
    }
};

struct selSortN {
    std::chrono::microseconds operator()(uint64_t n, int seed) const {
			srand(seed);
			BenchmarkTimer tmr(false);

			std::vector<int> contents = makeRandomNumberVector(n, 0, 2147483646, seed, false);
			Item *list = makeList(contents);

			tmr.start();
			list = LLSelectionSort(list);
			tmr.stop();

			deleteList(list);

			return tmr.getTime();
    }
};

TEST(SelSortJTest, SameElementManyTimesMin) {
	std::vector<int> contents({-1,1,1,3,5,6,7,15,5,5,5,1,4,6,7,1,20,20,21,99});

	Item * list = makeList(contents);
	int min = findMin(list)->getValue();

	EXPECT_EQ(-1, min);

	deleteList(list);
}

TEST(SelSortJTest, FirstElementMinSort) {
	std::vector<int> contents({-91, 5, 4, 3});
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTest, LastElementMinSort) {
	std::vector<int> contents({3, 5, 4, -91});
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTest, ThreeEqualValuesSort) {
	std::vector<int> contents({5,5,5});
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTest, ThreeEqualNegativeValuesSort) {
	std::vector<int> contents({-5,-5,-5});
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTest, ReversedListSort) {
	std::vector<int> contents({10,9,8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7,-8});
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

// Checks to make sure your code is not modifying the list pointers
// or swapping values
TEST(SelSortJTest, PointerIntegrity) {
	std::vector<int> contents({10,9,8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7,-8});
	std::map<Item*, int> pointers;
	Item * list = makeList(contents);
	Item* trav = list;
	while (trav != nullptr) {
		pointers[trav] = trav->getValue();
		trav = trav->next;
	}

	list = LLSelectionSort(list);

	trav = list;
	while (trav != nullptr) {
		if(pointers.find(trav) == pointers.end()) {
			FAIL();
		} else {
			// check to make sure value associated with pointer has not been altered
			EXPECT_EQ(trav->getValue(), pointers[trav]);
		}
		trav = trav->next;
	}

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	// ASSERT_TRUE(checkSameValues(list, contents));
	// ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTest, EmptyListMin) {
	EXPECT_EQ(nullptr, findMin(nullptr));
}

TEST(SelSortJTestStress, TenThousandElementMin) {
	removeStackLimit();
	std::vector<int> contents = makeRandomNumberVector(10000, -2147483646, 2147483646, 12345, true);

	Item * list = makeList(contents);
	int min = findMin(list)->getValue();

	EXPECT_EQ(*std::min_element(contents.begin(), contents.end()), min);

	deleteList(list);
}

TEST(SelSortJTestStress, HundredThousandElementMin) {
	removeStackLimit();
	std::vector<int> contents = makeRandomNumberVector(100000, -2147483646, 2147483646, 12345, true);

	Item * list = makeList(contents);
	int min = findMin(list)->getValue();

	EXPECT_EQ(*std::min_element(contents.begin(), contents.end()), min);

	deleteList(list);
}

TEST(SelSortJTestStress, MillionElementMin) {
	removeStackLimit();
	std::vector<int> contents = makeRandomNumberVector(1000000, -2147483646, 2147483646, 12345, true);
	Item * list = makeList(contents);
	int min = findMin(list)->getValue();

	EXPECT_EQ(*std::min_element(contents.begin(), contents.end()), min);

	deleteList(list);
}

TEST(SelSortJTestStress, HundredListSort) {
	removeStackLimit();
	std::vector<int> contents = makeRandomNumberVector(100, -2147483646, 2147483646, 12345, true);
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTestStress, ThousandListSort) {
	removeStackLimit();
	std::vector<int> contents = makeRandomNumberVector(1000, -2147483646, 2147483646, 12345, true);
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTestStress, TenThousandListSort) {
	removeStackLimit();
	std::vector<int> contents = makeRandomNumberVector(10000, -2147483646, 2147483646, 12345, true);
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTestStress, FiftyThousandListSort) {
	removeStackLimit();
	std::vector<int> contents = makeRandomNumberVector(50000, -2147483646, 2147483646, 12345, true);
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

// TEST(SelSortJTestRuntime, MinRunTimeEval) {
// 	removeStackLimit();
//
// 	RuntimeEvaluator::Snippet snp{findMinN()};
// 	RuntimeEvaluator rntm("findMin", 1, 20, 10, snp);
//   rntm.setCorrelationThreshold(1.1);
// 	rntm.evaluate();
// 	ASSERT_TRUE(rntm.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEAR));
// }

// TEST(SelSortJTestRuntime, SSortRunTimeEval) {
// 	removeStackLimit();
//
// 	RuntimeEvaluator::Snippet snp{selSortN()};
// 	RuntimeEvaluator rntm("selSort", 1, 12, 10, snp);
//   rntm.setCorrelationThreshold(1.5);
// 	rntm.evaluate();
// 	ASSERT_TRUE(rntm.meetsComplexity(RuntimeEvaluator::TimeComplexity::QUADRATIC));
// }
