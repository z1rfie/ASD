#include <windows.h>
#include <iostream>
#include "list.h"
#include <gtest/gtest.h>

TEST(TestListLib, default_constructor) {
	List<int> list;

	EXPECT_EQ(list.head(), nullptr);
	EXPECT_EQ(list.tail(), nullptr);
	EXPECT_EQ(list.count(), 0);
}

TEST(TestListLib, copy_constructor) {
	List<int> list1;
	list1.push_back(1); list1.push_back(2); list1.push_back(3);
	List<int> list2(list1);

	EXPECT_EQ(list2.head()->value, 1);
	EXPECT_EQ(list2.tail()->value, 3);
	EXPECT_EQ(list2.count(), 3);
}

TEST(TestListLib, push_front) {
	List<int> list;
	list.push_front(3);
	list.push_front(2);
	list.push_front(1);

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.tail()->value, 3);
	EXPECT_EQ(list.count(), 3);
}

TEST(TestListLib, push_back) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.tail()->value, 3);
	EXPECT_EQ(list.count(), 3);
}

TEST(TestListLib, insert_by_position) {
	List<int> list;
	list.push_back(1);
	list.push_back(3);
	list.insert(1, 2); 

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.head()->next->value, 2);
	EXPECT_EQ(list.tail()->value, 3);
	EXPECT_EQ(list.count(), 3);
}

TEST(TestListLib, insert_by_node) {
	List<int> list;
	list.push_back(1);
	list.push_back(3);

	Node<int>* first = list.head();
	list.insert(first, 2); 

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.head()->next->value, 2);
	EXPECT_EQ(list.tail()->value, 3);
}

TEST(TestListLib, pop_front) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.pop_front();
	EXPECT_EQ(list.head()->value, 2);
	EXPECT_EQ(list.count(), 2);
}

TEST(TestListLib, pop_back) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.pop_back();
	EXPECT_EQ(list.tail()->value, 2);
	EXPECT_EQ(list.count(), 2);
}

TEST(TestListLib, erase_by_position) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.erase(1); 
	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.tail()->value, 3);
	EXPECT_EQ(list.count(), 2);
}

TEST(TestListLib, erase_by_node) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	Node<int>* middle = list.head()->next;
	list.erase(middle);

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.tail()->value, 3);
	EXPECT_EQ(list.count(), 2);
}

TEST(TestListLib, is_empty) {
	List<int> list;
	EXPECT_TRUE(list.is_empty());

	list.push_back(1);
	EXPECT_FALSE(list.is_empty());

	list.pop_front();
	EXPECT_TRUE(list.is_empty());
}

TEST(TestListLib, count) {
	List<int> list;
	EXPECT_EQ(list.count(), 0);

	list.push_back(1);
	EXPECT_EQ(list.count(), 1);

	list.push_back(2);
	EXPECT_EQ(list.count(), 2);

	list.pop_front();
	EXPECT_EQ(list.count(), 1);
}