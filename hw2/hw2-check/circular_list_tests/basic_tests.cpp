#include <gtest/gtest.h>

#include <circular_list_int.h>

#include <circular_list_utils.h>

// ----------------------------------------
// CS104 HW2 Problem 1 basic test file
// ----------------------------------------

// This file is meant both as an example of the testing functions, and as a way to 
// help ensure that your code at least works at a very basic level.

// It is not meant to be a complete test suite; passing these tests is no guarantee that your code will score well.
// Rather, we encourage you to study the logic used here and use it to create your own more comprehensive tests.
// Corner cases, stress tests, boundary conditions -- test for as many as you can think of, since we *will* be checking for them.

// just construct a list without doing anything
TEST(ListBasic, ConstructionDestruction)
{
	CircularListInt list;
}

// add one item and check that it's there
TEST(ListBasic, OneItemAdd)
{
	CircularListInt list;

	list.push_back(999);

	EXPECT_EQ(999, list.get(0));
	EXPECT_EQ(1, list.size());
	EXPECT_EQ(false, list.empty());
}

// add three items and check that they're there
TEST(ListBasic, ThreeItemAdd)
{
	// this test shows how to use some of the testing utility functions
	// in circular_list_utils.h

	// first we create a vector to hold our data
	std::vector<int> contents{768, 1024, 1536};

	// then we create a new list with that data
	CircularListInt * populatedList = makeCircularList(contents);

	// next, we print the contents of the list
	std::cout << "List was: " << std::endl;
	printList(populatedList);

	// then we assert that the list contains that data
	EXPECT_TRUE(checkListContent(populatedList, contents));

	delete populatedList;
}

// check that size() and empty() perform correctly on an empty list
TEST(ListBasic, Empty)
{
	CircularListInt list;

	EXPECT_EQ(0, list.size());
	EXPECT_EQ(true, list.empty());
}

// check that one item can be removed
TEST(ListBasic, OneItemRemove)
{
	CircularListInt list;

	list.push_back(-3);

	EXPECT_EQ(-3, list.get(0));
	EXPECT_EQ(1, list.size());
	EXPECT_EQ(false, list.empty());

	list.remove(0);

	EXPECT_EQ(0, list.size());
	EXPECT_EQ(true, list.empty());
}

// check that three items can be removed (in start-to-end order)
TEST(ListBasic, ThreeItemRemove)
{
	std::vector<int> contents{7, 90000, 4};

	CircularListInt * populatedList = makeCircularList(contents);

	EXPECT_TRUE(checkListContent(populatedList, contents));

	// remove elements one-by-one and check that they have been removed
	do
	{
		populatedList->remove(0);
		contents.erase(contents.begin());

		EXPECT_TRUE(checkListContent(populatedList, contents));
	}
	while(!contents.empty());

	delete populatedList;
}

// try setting items
TEST(ListBasic, Set)
{
	std::vector<int> contents{0, -5043, 200};

	CircularListInt * populatedList = makeCircularList(contents);

	EXPECT_TRUE(checkListContent(populatedList, contents));

	populatedList->set(0, 2);
	contents[0] = 2;

	populatedList->set(2, 0);
	contents[2] = 0;

	EXPECT_TRUE(checkListContent(populatedList, contents));

	delete populatedList;
}

// check that indicies wrap around properly
TEST(ListBasic, CircularIndicies)
{
	std::vector<int> contents{-20, -1, 1};

	CircularListInt * populatedList = makeCircularList(contents);

	EXPECT_TRUE(checkListContent(populatedList, contents));

	// first try some gets
	EXPECT_EQ(-20, populatedList->get(3));
	EXPECT_EQ(1, populatedList->get(5));
	EXPECT_EQ(-1, populatedList->get(10));

	// now try setting an item
	populatedList->set(4, 7998);
	EXPECT_EQ(7998, populatedList->get(7));

	delete populatedList;
}