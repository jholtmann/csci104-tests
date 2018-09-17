#include <gtest/gtest.h>

#include <stackint.h>

// just construct a list without doing anything
TEST(StackIntBasic, ConstructionDestruction)
{
    StackInt stack;
}

// add one item and check that it's there
TEST(StackIntBasic, OneItemAdd)
{
    StackInt stack;

    stack.push(999);

    EXPECT_EQ(999, stack.top());
    EXPECT_EQ(false, stack.empty());
}

// add one item and remove it
TEST(StackIntBasic, OneItemAdd)
{
    StackInt stack;

    stack.push(999);
    stack.pop();

    // Not sure what stack.top() should return when list is empty
    //EXPECT_EQ(999, stack.top());
    EXPECT_EQ(true, stack.empty());
}
