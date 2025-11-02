#include <windows.h>
#include <iostream>
#include "list.h"
#include "../lib_tvector/vector.h"
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

TEST(TestListLib, is_empty) {
	List<int> list;
	EXPECT_TRUE(list.is_empty());

	list.push_back(1);
	EXPECT_FALSE(list.is_empty());

	list.pop_front();
	EXPECT_TRUE(list.is_empty());
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

TEST(TestListLib, push_front_one_elem) {
	List<int> list;
	list.push_front(42);

	EXPECT_EQ(list.head()->value, 42);
	EXPECT_EQ(list.tail()->value, 42);
	EXPECT_EQ(list.count(), 1);
	EXPECT_FALSE(list.is_empty());
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

TEST(TestListLib, push_back_one_elem) {
	List<int> list;
	list.push_back(42);

	EXPECT_EQ(list.head()->value, 42);
	EXPECT_EQ(list.tail()->value, 42);
	EXPECT_EQ(list.count(), 1);
	EXPECT_FALSE(list.is_empty());
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

TEST(TestListLib, insert_by_pos_null_throw) {
	List<int> list;

	EXPECT_THROW(list.insert(3, 1), std::out_of_range);
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

TEST(TestListLib, insert_after_tail) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);

	Node<int>* tail = list.tail();
	list.insert(tail, 3); 

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.head()->next->value, 2);
	EXPECT_EQ(list.tail()->value, 3);
	EXPECT_EQ(list.count(), 3);
}

TEST(TestListLib, insert_null_throw) {
	List<int> list;

	EXPECT_THROW(list.insert(nullptr, 1), std::invalid_argument);
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

TEST(TestListLib, pop_front_empty_list) {
	List<int> list;

	EXPECT_THROW(list.pop_front(), std::runtime_error);
}

TEST(TestListLib, pop_front_one_elem) {
	List<int> list;
	list.push_back(42);

	list.pop_front();

	EXPECT_EQ(list.is_empty(), true);
	EXPECT_EQ(list.count(), 0);
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

TEST(TestListLib, pop_back_empty_list) {
	List<int> list;

	EXPECT_THROW(list.pop_back(), std::runtime_error);
}

TEST(TestListLib, pop_back_one_elem) {
	List<int> list;
	list.push_back(42);

	list.pop_back();

	EXPECT_EQ(list.is_empty(), true);
	EXPECT_EQ(list.count(), 0);
}

TEST(TestListLib, erase_by_pos) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.erase(1); 

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.tail()->value, 3);
	EXPECT_EQ(list.count(), 2);
	EXPECT_EQ(list.head()->next, list.tail());
}

TEST(TestListLib, erase_last_elem) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.erase(2); 

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.tail()->value, 2);
	EXPECT_EQ(list.count(), 2);
	EXPECT_EQ(list.tail()->next, nullptr);
}

TEST(TestListLib, erase_invalid_pos) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);

	EXPECT_THROW(list.erase(5), std::out_of_range);
	EXPECT_THROW(list.erase(2), std::out_of_range); 
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

TEST(TestListLib, erase_head_node) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	Node<int>* head = list.head();
	list.erase(head);

	EXPECT_EQ(list.head()->value, 2);
	EXPECT_EQ(list.tail()->value, 3);
	EXPECT_EQ(list.count(), 2);
}

TEST(TestListLib, erase_tail_node) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	Node<int>* tail = list.tail();
	list.erase(tail);

	EXPECT_EQ(list.head()->value, 1);
	EXPECT_EQ(list.tail()->value, 2);
	EXPECT_EQ(list.count(), 2);
	EXPECT_EQ(list.tail()->next, nullptr);
}

TEST(TestListLib, erase_node_null) {
	List<int> list;
	list.push_back(1);

	EXPECT_THROW(list.erase(nullptr), std::invalid_argument);
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

TEST(TestListLib, iterator_read) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i * 3 + 1);
	}

	int expected_values[5] = { 1, 4, 7, 10, 13 };

	int index = 0;
	for (auto it = list.begin(); it != list.end(); ++it) {
		EXPECT_EQ(*it, expected_values[index++]);
	}
}

TEST(TestListLib, iterator_write) {
	List<int> list;

	int new_value = 100;
	for (auto it = list.begin(); it != list.end(); ++it) {
		*it = new_value++;
	}

	int expected_values[5] = { 100, 101, 102, 103, 104 };

	int index = 0;
	for (auto it = list.begin(); it != list.end(); ++it) {
		EXPECT_EQ(*it, expected_values[index++]);
	}
}

TEST(TestListLib, iterate_empty_list) {
	List<int> list; 

	int iterations = 0;
	for (auto it = list.begin(); it != list.end(); ++it) {
		iterations++;
	}
	EXPECT_EQ(iterations, 0);
}