#include <gtest/gtest.h>
#include <circular_list_int.h>
#include <circular_list_utils.h>

/* 	AUTHOR: JONATHAN HOLTMANN
		EMAIL: holtmann@usc.edu
		DESCIPTION: The following contains extra test cases for the CSCI 104
								homework assignment nr. 2
*/

TEST(ListJTest, WrapAround) {
	std::vector<int> contents;
	CircularListInt *list = new CircularListInt();

	for (int i = 0; i < 10; i++) {
  	contents.push_back(i);
  	list->push_back(i);
	}

	EXPECT_EQ(list->get(5), list->get(15));
	EXPECT_EQ(list->get(0), list->get(10));

	delete list;
}

TEST(ListJTest, SetManyItems) {
	std::vector<int> contents{0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0};

	CircularListInt * populatedList = makeCircularList(contents);
	for (int i = 4; i < 14; i++) {
		populatedList->set(i, 0);
	}

	for (int i = 0; i < 20; i++) {
		EXPECT_EQ(0, populatedList->get(i));
	}

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

TEST(ListJTest, RemoveMiddle) {
	std::vector<int> contents{8, 953, 4, 200, 68};
	CircularListInt *list = makeCircularList(contents);
	//printList(list);
	list->remove(3);
	contents.erase(contents.begin() + 3);
	//printList(list);

	EXPECT_EQ(contents.size(), list->size());
	EXPECT_TRUE(checkListContent(list, contents));

	delete list;
}

TEST(ListJTest, FillEmptyFill) {
	std::vector<int> contents{8, 953, 4, 200, 68};
	CircularListInt *list = makeCircularList(contents);

	while (contents.size() > 0) {
		list->remove(0);
		contents.erase(contents.begin());
	}

	EXPECT_EQ(0, list->size());
	EXPECT_TRUE(checkListContent(list, contents));

	std::vector<int> contents2{9,512,2134,-5312,5321,-6,6,-9};
	for (size_t i = 0; i < contents2.size(); i++)
		list->push_back(contents2[i]);

	EXPECT_EQ(contents2.size(), list->size());
	EXPECT_TRUE(checkListContent(list, contents2));

	delete list;
}

TEST(ListJTestStress, TenThousandListCreate) {
	std::vector<int> contents;
	for (int i = -5000; i <= 5000; i++) {
		contents.push_back(i);
	}
	CircularListInt *list = makeCircularList(contents);

	EXPECT_EQ(contents.size(), list->size());
	EXPECT_TRUE(checkListContent(list, contents));

	delete list;
}

TEST(ListJTestStress, HundredThousandListCreate) {
	std::vector<int> contents;
	for (int i = -50000; i <= 50000; i++) {
		contents.push_back(i);
	}
	CircularListInt *list = makeCircularList(contents);

	EXPECT_EQ(contents.size(), list->size());
	EXPECT_TRUE(checkListContent(list, contents));

	delete list;
}
