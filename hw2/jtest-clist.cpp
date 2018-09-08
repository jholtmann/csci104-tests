#include <gtest/gtest.h>
#include <circular_list_int.h>
#include <circular_list_utils.h>

/* 	AUTHOR: JONATHAN HOLTMANN
		EMAIL: holtmann@usc.edu
		DESCIPTION: The following contains extra test cases for the CSCI 104
								homework assignment nr. 2/
*/

TEST(ListJTest, CircularIndicies) {
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

TEST(ListJTest, SetSingleItem) {
	std::vector<int> contents{0};

	CircularListInt * populatedList = makeCircularList(contents);

	EXPECT_TRUE(checkListContent(populatedList, contents));

	populatedList->set(0, 2);
	contents[0] = 2;

	EXPECT_TRUE(checkListContent(populatedList, contents));

	delete populatedList;
}

TEST(ListJTest, SetEmptyList) {
	std::vector<int> contents{0};

	CircularListInt * list = new CircularListInt();

	list->set(0, 2);
	contents[0] = 2;

	EXPECT_EQ(0, list->get(0));

	delete list;
}

TEST(ListJTest, AddItemsSize) {
	std::vector<int> contents;
	CircularListInt *list = new CircularListInt();

	for (int i = 0; i < 10; i++) {
		contents.push_back(i);
		list->push_back(i);
	}

	EXPECT_EQ(list->size(), contents.size());
	EXPECT_TRUE(checkListContent(list, contents));

	delete list;
}

TEST(ListJTest, RepeatedRemoveHead) {
	std::vector<int> contents{6,13,5,2,7,9,1,4,6,8};
	CircularListInt *list = makeCircularList(contents);

	while (contents.size() > 0) {
		list->remove(0);
		contents.erase(contents.begin());
	}

	EXPECT_EQ(contents.size(), list->size());
	EXPECT_TRUE(checkListContent(list, contents));

	delete list;
}
