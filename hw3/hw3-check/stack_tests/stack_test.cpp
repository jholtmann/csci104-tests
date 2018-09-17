#include <gtest/gtest.h>
#include <random_generator.h>
#include <stackint.h>

TEST(JTestStack, MakeStack) {
	StackInt stack;
}

TEST(JTestStack, SingleItemStack) {
	StackInt stack;
	stack.push(0);
}

// add one item and check that it's there
TEST(JTestStack, OneItemAdd)
{
    StackInt stack;

    stack.push(999);

    EXPECT_EQ(999, stack.top());
    EXPECT_EQ(false, stack.empty());
}

// add one item and remove it
TEST(JTestStack, OneItemAddRemove)
{
    StackInt stack;

    stack.push(999);
    stack.pop();

    // Not sure what stack.top() should return when list is empty
    //EXPECT_EQ(999, stack.top());
    EXPECT_EQ(true, stack.empty());
}

TEST(JTestStack, SingleItemSetRetrieve) {
	StackInt stack;
	stack.push(0);
	EXPECT_EQ(stack.top(), 0);
}

TEST(JTestStack, SingleItemEmpty) {
	StackInt stack;
	stack.push(0);
	stack.pop();
	ASSERT_TRUE(stack.empty() == true);
}

TEST(JTestStack, FillEmpty) {
	StackInt stack;
	std::vector<int> vec = makeRandomIntVector(10, 12345, true);
	for (int i : vec) {
		stack.push(i);
	}

	int counter = 9;
	while(!stack.empty()) {
		EXPECT_EQ(stack.top(), vec[counter--]);
		stack.pop();
	}
}

TEST(JTestStack, FillEmptyFill) {
	StackInt stack;
	std::vector<int> vec1 = makeRandomIntVector(10, 12345, true);
	for (int i : vec1) {
		stack.push(i);
	}

	int counter = 9;
	while(!stack.empty()) {
		EXPECT_EQ(stack.top(), vec1[counter--]);
		stack.pop();
	}
	ASSERT_TRUE(stack.empty() == true);

	std::vector<int> vec2 = makeRandomIntVector(10, 54321, true);
	for (int i : vec2) {
		stack.push(i);
	}

	counter = 9;
	while(!stack.empty()) {
		EXPECT_EQ(stack.top(), vec2[counter--]);
		stack.pop();
	}
	ASSERT_TRUE(stack.empty() == true);
}

TEST(JTestStackStress, TenThousandFillEmpty) {
	StackInt stack;
	std::vector<int> vec = makeRandomIntVector(10000, 12345, true);
	for (int i : vec) {
		stack.push(i);
	}

	int counter = 9999;
	while(!stack.empty()) {
		EXPECT_EQ(stack.top(), vec[counter--]);
		stack.pop();
	}
}

TEST(JTestStackStress, FiftyThousandFillEmpty) {
	StackInt stack;
	std::vector<int> vec = makeRandomIntVector(50000, 12345, true);
	for (int i : vec) {
		stack.push(i);
	}

	int counter = 49999;
	while(!stack.empty()) {
		EXPECT_EQ(stack.top(), vec[counter--]);
		stack.pop();
	}
}
