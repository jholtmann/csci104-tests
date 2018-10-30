#include <gtest/gtest.h>

#include <selection_sort.h>

#include <selection_sort_utils.h>

// ----------------------------------------
// CS104 HW2 Problem 1 basic test file
// ----------------------------------------

// This file is meant both as an example of the testing functions, and as a way to 
// help ensure that your code at least works at a very basic level.

// It is not meant to be a complete test suite; passing these tests is no guarantee that your code will score well.
// Rather, we encourage you to study the logic used here and use it to create your own more comprehensive tests.
// Corner cases, stress tests, boundary conditions -- test for as many as you can think of, since we *will* be checking for them.

// Good luck, and happy testing!  --CP Jamie

TEST(SelSortBasic, OneElementFindMin)
{
	// First, create a vector of the contents you want in your list
	std::vector<int> contents({0});

	// now, use a testing function to create a list from those those numbers
	Item * list = makeList(contents);

	// now look for the min
	int min = findMin(list)->getValue();

	// ...and check that it's right
	EXPECT_EQ(0, min);

	// finally, delete the list using another test function
	deleteList(list);
}

TEST(SelSortBasic, ThreeElementFindMin)
{
	std::vector<int> contents({1, 0, -1});

	Item * list = makeList(contents);

	int min = findMin(list)->getValue();

	EXPECT_EQ(-1, min);

	deleteList(list);
}

TEST(SelSortBasic, TenElementFindMin)
{
	// First, create a vector of the contents you want in your list.  Let's make a bit bigger list this time...
	std::vector<int> contents({9000, -870, 7, 9, 4, 0, 200, 9000, 370, -10});

	// now, use a testing function to create a list from those those numbers
	Item * list = makeList(contents);

	// now look for the min
	int min = findMin(list)->getValue();

	// ...and check that it's right.  Since the list is a bit bigger, we can use a testing function to find the min
	EXPECT_EQ(getMinValue(contents), min);

	// finally, delete the list using another test function
	deleteList(list);
}

TEST(SelSortBasic, ThreeElementSort)
{
	// Now, let's cover how to set up a LLSelectionSort() test.
	// First, create a vector of the contents you want in your list.
	std::vector<int> contents({3, 1, 2});

	// now, use a testing function to create a list from those those numbers
	Item * list = makeList(contents);

	// now, sort the list
	list = LLSelectionSort(list);

	// next, use a testing function to verify the pointers in the list
	ASSERT_TRUE(checkValidPointers(list, contents.size()));

	// next, use a testing function to verify that the sorted list contains the same values as the original list
	ASSERT_TRUE(checkSameValues(list, contents));

	// finally, use a testing function to verify that the list is actually sorted in least-to-greatest order.
	ASSERT_TRUE(checkIsSorted(list));

	// of course, don't forget to delete the list
	deleteList(list);
}

TEST(SelSortBasic, TenElementSort)
{
	// Now, let's redo the previous test with a few more elements.
	std::vector<int> contents({9000, -870, 7, 9, 4, 0, 200, 9000, 370, -10});

	Item * list = makeList(contents);
	list = LLSelectionSort(list);

	ASSERT_TRUE(checkValidPointers(list, contents.size()));
	ASSERT_TRUE(checkSameValues(list, contents));
	ASSERT_TRUE(checkIsSorted(list));

	deleteList(list);
}