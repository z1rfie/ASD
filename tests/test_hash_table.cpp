#include <gtest/gtest.h>
#include "hash_table.h"

TEST(TestHashTable, is_empty) {
    HashTable<int> ht(10);
    EXPECT_TRUE(ht.is_empty());
}

TEST(TestHashTable, not_empty) {
    HashTable<int> ht(10);
    ht.insert("key", 42);
    EXPECT_FALSE(ht.is_empty());
}

TEST(TestHashTable, insert_and_found) {
    HashTable<int> ht(10);
    ht.insert("age", 25);
    EXPECT_EQ(ht.found("age"), 25);
}

TEST(TestHashTable, insert_and_found_string) {
    HashTable<std::string> ht(10);
    ht.insert("name", "Alice");
    EXPECT_EQ(ht.found("name"), "Alice");
}

TEST(TestHashTable, insert) {
    HashTable<int> ht(10);
    ht.insert("a", 1);
    ht.insert("b", 2);
    ht.insert("c", 3);
    EXPECT_EQ(ht.found("a"), 1);
    EXPECT_EQ(ht.found("b"), 2);
    EXPECT_EQ(ht.found("c"), 3);
}

TEST(TestHashTable, found_returns_reference) {
    HashTable<int> ht(10);
    ht.insert("x", 10);
    ht.found("x") = 99;
    EXPECT_EQ(ht.found("x"), 99);
}

TEST(TestHashTable, insert_duplicate_throws) {
    HashTable<int> ht(10);
    ht.insert("dup", 1);
    EXPECT_THROW(ht.insert("dup", 2), std::runtime_error);
}

TEST(TestHashTable, found_missing_key_throws) {
    HashTable<int> ht(10);
    EXPECT_THROW(ht.found("missing"), std::runtime_error);
}

TEST(TestHashTable, erase_existing_key) {
    HashTable<int> ht(10);
    ht.insert("key", 42);
    ht.erase("key");
    EXPECT_THROW(ht.found("key"), std::runtime_error);
}

TEST(TestHashTable, erase_non_existing_key_throws) {
    HashTable<int> ht(10);
    EXPECT_THROW(ht.erase("ghost"), std::runtime_error);
}

TEST(TestHashTable, isEmpty_after_erase_all_keys) {
    HashTable<int> ht(10);
    ht.insert("a", 1);
    ht.erase("a");
    EXPECT_TRUE(ht.is_empty());
}

TEST(TestHashTable, insert_after_erase) {
    HashTable<int> ht(10);
    ht.insert("key", 1);
    ht.erase("key");
    ht.insert("key", 2);
    EXPECT_EQ(ht.found("key"), 2);
}

TEST(TestHashTable, find_key_after_collision_and_erase) {
    HashTable<int> ht(10);
    ht.insert("k1", 1);
    ht.insert("k2", 2);
    ht.insert("k3", 3);
    ht.erase("k2");
    EXPECT_EQ(ht.found("k1"), 1);
    EXPECT_EQ(ht.found("k3"), 3);
    EXPECT_THROW(ht.found("k2"), std::runtime_error);
}

TEST(TestHashTable, overflow_throws) {
    HashTable<int> ht(3);
    ht.insert("a", 1);
    ht.insert("b", 2);
    ht.insert("c", 3);
    EXPECT_THROW(ht.insert("d", 4), std::runtime_error);
}

TEST(TestHashTable, collision_insert_and_found) {
    HashTable<int> ht(10);
    ht.insert("ab", 1);
    ht.insert("ba", 2); 
    EXPECT_EQ(ht.found("ab"), 1);
    EXPECT_EQ(ht.found("ba"), 2);
}