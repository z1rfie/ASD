#include <windows.h>
#include <iostream>
#include "list_stack.h"
#include <gtest/gtest.h>

TEST(TestListStackLib, init_constructor) {
    ListStack<int> stack;

    EXPECT_TRUE(stack.is_empty());
}

TEST(TestListStackLib, copy_constructor) {
    ListStack<double> stack1;
    stack1.push(3.14);
    stack1.push(5.1);
    ListStack<double> stack2(stack1);

    EXPECT_EQ(stack2.top(), 5.1);
    EXPECT_FALSE(stack2.is_empty());
}

TEST(TestListStackLib, push) {
    ListStack<int> stack;
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    EXPECT_EQ(stack.top(), 15);
    EXPECT_FALSE(stack.is_empty());
}

TEST(TestListStackLib, pop) {
    ListStack<int> stack;
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    stack.pop();

    EXPECT_EQ(stack.top(), 14);
    EXPECT_FALSE(stack.is_empty());
}

TEST(TestListStackLib, pop_error) {
    ListStack<int> stack;

    EXPECT_THROW(stack.pop(), std::runtime_error);
    EXPECT_TRUE(stack.is_empty());
}

TEST(TestListStackLib, top) {
    ListStack<int> stack;
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);

    EXPECT_EQ(stack.top(), 6);
}

TEST(TestListStackLib, top_error) {
    ListStack<int> stack;

    EXPECT_THROW(stack.top(), std::runtime_error);
    EXPECT_TRUE(stack.is_empty());
}

TEST(TestListStackLib, is_empty) {
    ListStack<int> stack;

    EXPECT_TRUE(stack.is_empty());
}

TEST(TestListStackLib, not_empty) {
    ListStack<int> stack;
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);

    EXPECT_FALSE(stack.is_empty());
}

TEST(TestListStackLib, clear) {
    ListStack<int> stack;
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    stack.clear();

    EXPECT_TRUE(stack.is_empty());
}