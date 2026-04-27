#include <gtest/gtest.h>
#include "../lib_heap/heap.h"
#include "../lib_priority_queue/priority_queue.h"

TEST(TestHeap, default_constructor) {
    Heap<int> h;
    EXPECT_TRUE(h.is_empty());
    EXPECT_EQ(h.size(), 0);
}

TEST(TestHeap, push_single) {
    Heap<int> h;
    h.push(42);
    EXPECT_FALSE(h.is_empty());
    EXPECT_EQ(h.size(), 1);
    EXPECT_EQ(h.top(), 42);
}

TEST(TestHeap, push_multiple_size) {
    Heap<int> h;
    h.push(5);
    h.push(3);
    h.push(8);
    h.push(1);
    EXPECT_EQ(h.size(), 4);
}

TEST(TestHeap, top_is_minimum) {
    Heap<int> h;
    h.push(10);
    h.push(3);
    h.push(7);
    h.push(1);
    h.push(5);
    EXPECT_EQ(h.top(), 1);
}

TEST(TestHeap, top_does_not_remove) {
    Heap<int> h;
    h.push(5);
    h.push(2);
    h.push(8);
    h.top();
    EXPECT_EQ(h.size(), 3);
    EXPECT_EQ(h.top(), 2);
}

TEST(TestHeap, pop_returns_minimum) {
    Heap<int> h;
    h.push(10);
    h.push(3);
    h.push(7);
    h.push(1);
    EXPECT_EQ(h.pop(), 1);
}

TEST(TestHeap, pop_decreases_size) {
    Heap<int> h;
    h.push(5);
    h.push(2);
    h.push(8);
    h.pop();
    EXPECT_EQ(h.size(), 2);
}

TEST(TestHeap, pop_sorted_order) {
    Heap<int> h;
    h.push(5);
    h.push(3);
    h.push(8);
    h.push(1);
    h.push(4);
    EXPECT_EQ(h.pop(), 1);
    EXPECT_EQ(h.pop(), 3);
    EXPECT_EQ(h.pop(), 4);
    EXPECT_EQ(h.pop(), 5);
    EXPECT_EQ(h.pop(), 8);
}

TEST(TestHeap, pop_until_empty) {
    Heap<int> h;
    h.push(2);
    h.push(1);
    h.push(3);
    h.pop();
    h.pop();
    h.pop();
    EXPECT_TRUE(h.is_empty());
    EXPECT_EQ(h.size(), 0);
}

TEST(TestHeap, pop_empty_throws) {
    Heap<int> h;
    EXPECT_THROW(h.pop(), std::runtime_error);
}

TEST(TestHeap, top_empty_throws) {
    Heap<int> h;
    EXPECT_THROW(h.top(), std::runtime_error);
}

TEST(TestHeap, push_duplicates) {
    Heap<int> h;
    h.push(3);
    h.push(3);
    h.push(3);
    EXPECT_EQ(h.size(), 3);
    EXPECT_EQ(h.pop(), 3);
    EXPECT_EQ(h.pop(), 3);
    EXPECT_EQ(h.pop(), 3);
    EXPECT_TRUE(h.is_empty());
}

TEST(TestHeap, push_already_sorted) {
    Heap<int> h;
    h.push(1);
    h.push(2);
    h.push(3);
    h.push(4);
    h.push(5);
    EXPECT_EQ(h.pop(), 1);
    EXPECT_EQ(h.pop(), 2);
    EXPECT_EQ(h.pop(), 3);
}

TEST(TestHeap, push_reverse_sorted) {
    Heap<int> h;
    h.push(5);
    h.push(4);
    h.push(3);
    h.push(2);
    h.push(1);
    EXPECT_EQ(h.pop(), 1);
    EXPECT_EQ(h.pop(), 2);
    EXPECT_EQ(h.pop(), 3);
}

TEST(TestHeap, push_negative_values) {
    Heap<int> h;
    h.push(-5);
    h.push(-1);
    h.push(-3);
    EXPECT_EQ(h.top(), -5);
    EXPECT_EQ(h.pop(), -5);
    EXPECT_EQ(h.pop(), -3);
    EXPECT_EQ(h.pop(), -1);
}

TEST(TestHeap, push_mixed_negative_positive) {
    Heap<int> h;
    h.push(3);
    h.push(-2);
    h.push(0);
    h.push(-5);
    h.push(1);
    EXPECT_EQ(h.pop(), -5);
    EXPECT_EQ(h.pop(), -2);
    EXPECT_EQ(h.pop(), 0);
}

TEST(TestHeap, is_empty_after_push_pop) {
    Heap<int> h;
    EXPECT_TRUE(h.is_empty());
    h.push(1);
    EXPECT_FALSE(h.is_empty());
    h.pop();
    EXPECT_TRUE(h.is_empty());
}

TEST(TestHeap, push_pop_interleaved) {
    Heap<int> h;
    h.push(5);
    h.push(2);
    EXPECT_EQ(h.pop(), 2);
    h.push(1);
    h.push(8);
    EXPECT_EQ(h.pop(), 1);
    EXPECT_EQ(h.pop(), 5);
    EXPECT_EQ(h.pop(), 8);
    EXPECT_TRUE(h.is_empty());
}

TEST(TestHeap, large_input) {
    Heap<int> h;
    for (int i = 100; i >= 1; i--)
        h.push(i);
    EXPECT_EQ(h.size(), 100);
    for (int i = 1; i <= 100; i++)
        EXPECT_EQ(h.pop(), i);
    EXPECT_TRUE(h.is_empty());
}

TEST(TestHeap, print_does_not_crash) {
    Heap<int> h;
    h.push(3);
    h.push(1);
    h.push(2);
    EXPECT_NO_THROW(h.print());
}

TEST(TestPriotityQueue, prioritet) {
    PriorityQueue<int> q;
    for (int i = 0; i < 20; i++) {
        int prioritet = 1 + rand() % 5;
        int value = 100 + rand() % 900;
        q.push(value, prioritet);
        std::cout << value << " (" << prioritet << ") ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 5; i++) {
       int value = q.pop();
        std::cout << value << " ";
    }
}