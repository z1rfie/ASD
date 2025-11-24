#include <windows.h>
#include <iostream>
#include "list_queue.h"
#include <gtest/gtest.h>

TEST(TestListQueueLib, init_constructor) {
	ListQueue<int> q;

	EXPECT_TRUE(q.is_empty());
}

TEST(TestListQueueLib, copy_constructor) {
	ListQueue<int> q1;
	q1.push(777);
	q1.push(888);
	q1.push(999);
	ListQueue<int> q2(q1);

	EXPECT_EQ(q2.head(), 777);
	EXPECT_EQ(q2.tail(), 999);
	EXPECT_FALSE(q2.is_empty());
}

TEST(TestListQueueLib, push) {
	ListQueue<int> q;
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); q.push(666);
	q.push(777); q.push(888); q.push(999);

	EXPECT_EQ(q.head(), 111);
	EXPECT_EQ(q.tail(), 999);
	EXPECT_FALSE(q.is_empty());
}

TEST(TestListQueueLib, pop) {
	ListQueue<int> q;
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); q.push(666);
	q.push(777); q.push(888); q.push(999);

	q.pop();

	EXPECT_EQ(q.head(), 222);
	EXPECT_EQ(q.tail(), 999);
	EXPECT_FALSE(q.is_empty());
}

TEST(TestListQueueLib, pop_error) {
	ListQueue<int> q;

	EXPECT_THROW(q.pop(), std::runtime_error);
	EXPECT_TRUE(q.is_empty());
}

TEST(TestListQueueLib, tail) {
	ListQueue<int> q;
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555);

	q.pop(); q.pop();

	EXPECT_EQ(q.tail(), 555);
}

TEST(TestListQueueLib, tail_error) {
	ListQueue<int> q;

	EXPECT_THROW(q.tail(), std::runtime_error);
	EXPECT_TRUE(q.is_empty());
}

TEST(TestListQueueLib, head) {
	ListQueue<int> q;
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555);

	q.pop(); q.pop();

	EXPECT_EQ(q.head(), 333);
}

TEST(TestListQueueLib, head_error) {
	ListQueue<int> q;

	EXPECT_THROW(q.head(), std::runtime_error);
	EXPECT_TRUE(q.is_empty());
}

TEST(TestListQueueLib, not_empty) {
	ListQueue<int> q;
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); q.push(666);
	q.push(777); q.push(888); q.push(999);

	EXPECT_FALSE(q.is_empty());
}

TEST(TestListQueueLib, is_empty) {
	ListQueue<int> q;

	EXPECT_TRUE(q.is_empty());
}

TEST(TestListQueueLib, is_empty_after_pop) {
	ListQueue<int> q;

	q.push(111); q.pop();

	EXPECT_TRUE(q.is_empty());
}

TEST(TestListQueueLib, clear) {
	ListQueue<int> q;
	q.push(111); q.push(222); q.push(333);
	q.push(444); q.push(555); q.push(666);
	q.push(777); q.push(888); q.push(999);

	EXPECT_FALSE(q.is_empty());

	q.clear();

	EXPECT_TRUE(q.is_empty());
}