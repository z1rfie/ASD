#include <windows.h>
#include <iostream>
#include "stack.h"
#include <gtest/gtest.h>

TEST(TestStackLib, init_constructor) {
    Stack<int> stack(5);

    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(TestStackLib, copy_constructor) {
    Stack<double> stack1(4);
    stack1.push(3.14);
    stack1.push(5.1);
    Stack<double> stack2(stack1);
    
    EXPECT_EQ(stack2.top(), 5.1);
    EXPECT_FALSE(stack2.is_empty());
}

TEST(TestStackLib, push) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    EXPECT_EQ(stack.top(), 15);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_TRUE(stack.is_full());
}

TEST(TestStackLib, push_error) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    EXPECT_THROW(stack.push(777), std::runtime_error);
    EXPECT_EQ(stack.top(), 15);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_TRUE(stack.is_full());
}

TEST(TestStackLib, pop) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    stack.pop();

    EXPECT_EQ(stack.top(), 14);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(TestStackLib, pop_error) {
    Stack<int> stack(4);

    EXPECT_THROW(stack.pop(), std::runtime_error);
    EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackLib, top) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);

    EXPECT_EQ(stack.top(), 6);
}

TEST(TestStackLib, top_error) {
    Stack<int> stack(4);

    EXPECT_THROW(stack.top(), std::runtime_error);
    EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackLib, is_full) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    EXPECT_TRUE(stack.is_full());
}

TEST(TestStackLib, not_full) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);

    EXPECT_FALSE(stack.is_full());
}

TEST(TestStackLib, is_empty) {
    Stack<int> stack(8);

    EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackLib, not_empty) {
    Stack<int> stack(8);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);

    EXPECT_FALSE(stack.is_empty());
}

TEST(TestStackLib, clear) {
    Stack<int> stack(15);
    stack.push(1); stack.push(2); stack.push(3);
    stack.push(4); stack.push(5); stack.push(6);
    stack.push(7); stack.push(8); stack.push(9);
    stack.push(10); stack.push(11); stack.push(12);
    stack.push(13); stack.push(14); stack.push(15);

    stack.clear();

    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}