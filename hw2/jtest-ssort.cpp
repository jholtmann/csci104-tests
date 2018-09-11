#include <gtest/gtest.h>
#include <selection_sort.h>
#include <selection_sort_utils.h>
#include <misc_utils.h>
#include <map>
#include <chrono>

/* 	AUTHOR: JONATHAN HOLTMANN
		EMAIL: holtmann@usc.edu
		DESCIPTION: The following contains extra test cases for the CSCI 104
								homework assignment nr. 2
*/

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
	std::vector<int> contents;
	for (int i = 5000; i >= -5000; i--) {
		contents.push_back(i);
	}

	Item * list = makeList(contents);
	int min = findMin(list)->getValue();

	EXPECT_EQ(-5000, min);

	deleteList(list);
}

TEST(SelSortJTestStress, HundredThousandElementMin) {
	removeStackLimit();
	std::vector<int> contents;
	for (int i = 50000; i >= -50000; i--) {
		contents.push_back(i);
	}

	Item * list = makeList(contents);
	int min = findMin(list)->getValue();

	EXPECT_EQ(-50000, min);

	deleteList(list);
}

TEST(SelSortJTestStress, MillionElementMin) {
	removeStackLimit();
	std::vector<int> contents;
	for (int i = 500000; i >= -500000; i--) {
		contents.push_back(i);
	}

	Item * list = makeList(contents);
	int min = findMin(list)->getValue();

	EXPECT_EQ(-500000, min);

	deleteList(list);
}

TEST(SelSortJTestStress, HundredListSort) {
	removeStackLimit();
	std::vector<int> contents;
	for (int i = 50; i >= -50; i--) {
		contents.push_back(i);
	}
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTestStress, ThousandListSort) {
	removeStackLimit();
	std::vector<int> contents;
	for (int i = 500; i >= -500; i--) {
		contents.push_back(i);
	}
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTestStress, TenThousandListSort) {
	removeStackLimit();
	std::vector<int> contents;
	for (int i = 5000; i >= -5000; i--) {
		contents.push_back(i);
	}
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTestStress, FiftyThousandListSort) {
	removeStackLimit();
	std::vector<int> contents;
	for (int i = 25000; i >= -25000; i--) {
		contents.push_back(i);
	}
	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}

TEST(SelSortJTestRuntime, ThousandListMin) {
	removeStackLimit();
	double limit = 0.00075;
	limit *= 5;
	std::vector<int> contents;

	for (int i = 500; i >= -500; i--) {
		contents.push_back(i);
	}
	Item * list = makeList(contents);

	auto start = std::chrono::high_resolution_clock::now();
	findMin(list);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	EXPECT_GE(limit, diff.count());

	deleteList(list);
}

TEST(SelSortJTestRuntime, TenThousandListMin) {
	removeStackLimit();
	double limit = 0.00085;
	limit *= 5;
	std::vector<int> contents;

	for (int i = 5000; i >= -5000; i--) {
		contents.push_back(i);
	}
	Item * list = makeList(contents);

	auto start = std::chrono::high_resolution_clock::now();
	findMin(list);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	EXPECT_GE(limit, diff.count());

	deleteList(list);
}

TEST(SelSortJTestRuntime, HundredThousandListMin) {
	removeStackLimit();
	double limit = 0.0025;
	limit *= 5;
	std::vector<int> contents;

	for (int i = 50000; i >= -50000; i--) {
		contents.push_back(i);
	}
	Item * list = makeList(contents);

	auto start = std::chrono::high_resolution_clock::now();
	findMin(list);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	EXPECT_GE(limit, diff.count());

	deleteList(list);
}

TEST(SelSortJTestRuntime, MillionListMin) {
	removeStackLimit();
	double limit = 0.02;
	limit *= 5;
	std::vector<int> contents;

	for (int i = 500000; i >= -500000; i--) {
		contents.push_back(i);
	}
	Item * list = makeList(contents);

	auto start = std::chrono::high_resolution_clock::now();
	findMin(list);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	EXPECT_GE(limit, diff.count());

	deleteList(list);
}

TEST(SelSortJTestRuntime, ThousandListSort) {
	removeStackLimit();
	double limit = 0.02;
	limit *= 5;
	std::vector<int> contents;

	for (int i = 500; i >= -500; i--) {
		contents.push_back(i);
	}
	Item * list = makeList(contents);

	auto start = std::chrono::high_resolution_clock::now();
	list = LLSelectionSort(list);
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	EXPECT_GE(limit, diff.count());

	deleteList(list);
}

TEST(SelSortJTestRuntime, TenThousandListSort) {
	removeStackLimit();
	double limit = 0.9;
	limit *= 5;
	std::vector<int> contents;

	for (int i = 5000; i >= -5000; i--) {
		contents.push_back(i);
	}
	Item * list = makeList(contents);

	auto start = std::chrono::high_resolution_clock::now();
	list = LLSelectionSort(list);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	EXPECT_GE(limit, diff.count());

	deleteList(list);
}
