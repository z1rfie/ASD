#include <windows.h>
#include <iostream>
#include "../lib_doubly_linked_list/doubly_linked_list.h"
#include <gtest/gtest.h>

TEST(TestDoublyLinkedListLib, default_constructor) {
    DoublyLinkedList<int> list;

    EXPECT_EQ(list.head(), nullptr);
    EXPECT_EQ(list.tail(), nullptr);
    EXPECT_EQ(list.count(), 0);
}

TEST(TestDoublyLinkedListLib, copy_constructor) {
    DoublyLinkedList<int> list1;
    list1.push_back(1); list1.push_back(2); list1.push_back(3);
    DoublyLinkedList<int> list2(list1);

    EXPECT_EQ(list2.head()->value, 1);
    EXPECT_EQ(list2.tail()->value, 3);
    EXPECT_EQ(list2.count(), 3);
}

TEST(TestDoublyLinkedListLib, is_empty) {
    DoublyLinkedList<int> list;
    EXPECT_TRUE(list.is_empty());

    list.push_back(1);
    EXPECT_FALSE(list.is_empty());

    list.pop_front();
    EXPECT_TRUE(list.is_empty());
}

TEST(TestDoublyLinkedListLib, push_front) {
    DoublyLinkedList<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.tail()->value, 3);
    EXPECT_EQ(list.count(), 3);
}

TEST(TestDoublyLinkedListLib, push_front_one_elem) {
    DoublyLinkedList<int> list;
    list.push_front(42);

    EXPECT_EQ(list.head()->value, 42);
    EXPECT_EQ(list.tail()->value, 42);
    EXPECT_EQ(list.count(), 1);
    EXPECT_FALSE(list.is_empty());
}

TEST(TestDoublyLinkedListLib, push_back) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.tail()->value, 3);
    EXPECT_EQ(list.count(), 3);
}

TEST(TestDoublyLinkedListLib, push_back_one_elem) {
    DoublyLinkedList<int> list;
    list.push_back(42);

    EXPECT_EQ(list.head()->value, 42);
    EXPECT_EQ(list.tail()->value, 42);
    EXPECT_EQ(list.count(), 1);
    EXPECT_FALSE(list.is_empty());
}

TEST(TestDoublyLinkedListLib, insert_by_position) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insert(1, 2);

    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.head()->next->value, 2);
    EXPECT_EQ(list.tail()->value, 3);
    EXPECT_EQ(list.count(), 3);
}

TEST(TestDoublyLinkedListLib, insert_by_pos_null_throw) {
    DoublyLinkedList<int> list;

    EXPECT_THROW(list.insert(3, 1), std::out_of_range);
}

TEST(TestDoublyLinkedListLib, insert_by_node) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(3);

    Node<int>* first = list.head();
    list.insert(first, 2);

    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.head()->next->value, 2);
    EXPECT_EQ(list.tail()->value, 3);
}

TEST(TestDoublyLinkedListLib, insert_after_tail) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    Node<int>* tail = list.tail();
    list.insert(tail, 3);

    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.head()->next->value, 2);
    EXPECT_EQ(list.tail()->value, 3);
    EXPECT_EQ(list.count(), 3);
}

TEST(TestDoublyLinkedListLib, insert_null_throw) {
    DoublyLinkedList<int> list;

    EXPECT_THROW(list.insert(nullptr, 1), std::invalid_argument);
}

TEST(TestDoublyLinkedListLib, pop_front) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();
    EXPECT_EQ(list.head()->value, 2);
    EXPECT_EQ(list.count(), 2);
}

TEST(TestDoublyLinkedListLib, pop_front_empty_list) {
    DoublyLinkedList<int> list;

    EXPECT_THROW(list.pop_front(), std::runtime_error);
}

TEST(TestDoublyLinkedListLib, pop_front_one_elem) {
    DoublyLinkedList<int> list;
    list.push_back(42);

    list.pop_front();

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.count(), 0);
}

TEST(TestDoublyLinkedListLib, pop_back) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    EXPECT_EQ(list.tail()->value, 2);
    EXPECT_EQ(list.count(), 2);
}

TEST(TestDoublyLinkedListLib, pop_back_empty_list) {
    DoublyLinkedList<int> list;

    EXPECT_THROW(list.pop_back(), std::runtime_error);
}

TEST(TestDoublyLinkedListLib, pop_back_one_elem) {
    DoublyLinkedList<int> list;
    list.push_back(42);

    list.pop_back();

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.count(), 0);
}

TEST(TestDoublyLinkedListLib, erase_by_pos) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(2);

    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.tail()->value, 3);
    EXPECT_EQ(list.count(), 2);
    EXPECT_EQ(list.head()->next->value, 3);
}

TEST(TestDoublyLinkedListLib, erase_last_elem) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(3);

    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.tail()->value, 2);
    EXPECT_EQ(list.count(), 2);
    EXPECT_EQ(list.tail()->next, nullptr);
}

TEST(TestDoublyLinkedListLib, erase_invalid_pos) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    EXPECT_THROW(list.erase(5), std::out_of_range);
    EXPECT_THROW(list.erase(3), std::out_of_range);
}

TEST(TestDoublyLinkedListLib, erase_by_node) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* middle = list.head()->next;
    list.erase(middle);

    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.tail()->value, 3);
    EXPECT_EQ(list.count(), 2);
}

TEST(TestDoublyLinkedListLib, erase_head_node) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* head = list.head();
    list.erase(head);

    EXPECT_EQ(list.head()->value, 2);
    EXPECT_EQ(list.tail()->value, 3);
    EXPECT_EQ(list.count(), 2);
}

TEST(TestDoublyLinkedListLib, erase_tail_node) {
    DoublyLinkedList<int> list;
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

TEST(TestDoublyLinkedListLib, erase_node_null) {
    DoublyLinkedList<int> list;
    list.push_back(1);

    EXPECT_THROW(list.erase(nullptr), std::invalid_argument);
}

TEST(TestDoublyLinkedListLib, count) {
    DoublyLinkedList<int> list;
    EXPECT_EQ(list.count(), 0);

    list.push_back(1);
    EXPECT_EQ(list.count(), 1);

    list.push_back(2);
    EXPECT_EQ(list.count(), 2);

    list.pop_front();
    EXPECT_EQ(list.count(), 1);
}

TEST(TestDoublyLinkedListLib, iterator_read) {
    DoublyLinkedList<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i * 3 + 1);
    }

    int expected_values[5] = { 1, 4, 7, 10, 13 };

    int index = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected_values[index++]);
    }
}

TEST(TestDoublyLinkedListLib, iterator_write) {
    DoublyLinkedList<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }

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

TEST(TestDoublyLinkedListLib, iterate_empty_list) {
    DoublyLinkedList<int> list;

    int iterations = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        iterations++;
    }
    EXPECT_EQ(iterations, 0);
}

TEST(TestDoublyLinkedListLib, node_links_integrity) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* head = list.head();
    Node<int>* middle = head->next;
    Node<int>* tail = list.tail();

    EXPECT_EQ(head->next, middle);
    EXPECT_EQ(middle->prev, head);
    EXPECT_EQ(middle->next, tail);
    EXPECT_EQ(tail->prev, middle);
    EXPECT_EQ(tail->next, nullptr);
}