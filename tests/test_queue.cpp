#include <windows.h>
#include <iostream>
#include "queue.h"
#include <gtest/gtest.h>

TEST(TestQueueLib, init_constructor) {
	Queue<int> q(5);

	EXPECT_TRUE(q.is_empty());
	EXPECT_FALSE(q.is_full());
}

TEST(TestQueueLib, copy_constructor) {
	Queue<int> q1(5);
	q1.push(777);
	q1.push(888);
	q1.push(999);
	Queue<int> q2(q1);

	EXPECT_EQ(q2.head(), 777);
	EXPECT_EQ(q2.tail(), 999);
	EXPECT_FALSE(q2.is_empty());
}

TEST(TestQueueLib, push) {
	Queue<int> q(9);
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); q.push(666);
	q.push(777); q.push(888); q.push(999);

	EXPECT_EQ(q.head(), 111);
	EXPECT_EQ(q.tail(), 999);
	EXPECT_FALSE(q.is_empty());
	EXPECT_TRUE(q.is_full());
}

TEST(TestQueueLib, push_error) {
	Queue<int> q(9);
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); q.push(666);
	q.push(777); q.push(888); q.push(999);

	EXPECT_THROW(q.push(1010), std::runtime_error);
	EXPECT_EQ(q.head(), 111);
	EXPECT_EQ(q.tail(), 999);
	EXPECT_FALSE(q.is_empty());
	EXPECT_TRUE(q.is_full());
}

TEST(TestQueueLib, pop) {
	Queue<int> q(9);
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); q.push(666);
	q.push(777); q.push(888); q.push(999);

	q.pop();

	EXPECT_EQ(q.head(), 222);
	EXPECT_EQ(q.tail(), 999);
	EXPECT_FALSE(q.is_empty());
	EXPECT_FALSE(q.is_full());
}

TEST(TestQueueLib, pop_error) {
	Queue<int> q(9);

	EXPECT_THROW(q.pop(), std::runtime_error);
	EXPECT_TRUE(q.is_empty());
	EXPECT_FALSE(q.is_full());
}

TEST(TestQueueLib, tail) {
	Queue<int> q(9);
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); 

	q.pop(); q.pop();

	EXPECT_EQ(q.tail(), 555);
}

TEST(TestQueueLib, tail_error) {
	Queue<int> q(9);

	EXPECT_THROW(q.tail(), std::runtime_error);
	EXPECT_TRUE(q.is_empty());
	EXPECT_FALSE(q.is_full());
}

TEST(TestQueueLib, head) {
	Queue<int> q(9);
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555);

	q.pop(); q.pop();

	EXPECT_EQ(q.head(), 333);
}

TEST(TestQueueLib, head_error) {
	Queue<int> q(9);

	EXPECT_THROW(q.head(), std::runtime_error);
	EXPECT_TRUE(q.is_empty());
	EXPECT_FALSE(q.is_full());
}

TEST(TestQueueLib, not_empty) {
	Queue<int> q(9);
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); q.push(666);
	q.push(777); q.push(888); q.push(999);

	EXPECT_FALSE(q.is_empty());
	EXPECT_TRUE(q.is_full());
}

TEST(TestQueueLib, is_empty) {
	Queue<int> q(9);

	EXPECT_TRUE(q.is_empty());
	EXPECT_FALSE(q.is_full());
}

TEST(TestQueueLib, is_empty_after_pop) {
	Queue<int> q(9);

	q.push(111); q.pop();

	EXPECT_TRUE(q.is_empty());
	EXPECT_FALSE(q.is_full());
}

TEST(TestQueueLib, is_full) {
	Queue<int> q(9);
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); q.push(666);
	q.push(777); q.push(888); q.push(999);

	EXPECT_TRUE(q.is_full());
	EXPECT_FALSE(q.is_empty());
}

TEST(TestQueueLib, not_full) {
	Queue<int> q(9);

	EXPECT_FALSE(q.is_full());
}

TEST(TestQueueLib, clear) {
	Queue<int> q(9);
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); q.push(666);
	q.push(777); q.push(888); q.push(999);

	EXPECT_TRUE(q.is_full());

	q.clear();

	EXPECT_TRUE(q.is_empty());
}