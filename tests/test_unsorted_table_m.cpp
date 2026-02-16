#include <gtest/gtest.h>
#include "../lib_unsorted_table_m/unsorted_table_m.h"

TEST(TestUnsortedTableM, init_table) {
    UnsortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableM, insert_no_throw) {
    UnsortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    std::cout << table;
}

TEST(TestUnsortedTableM, insert_throw) {
    UnsortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    EXPECT_ANY_THROW(table.insert(2, "second"));
    std::cout << table;
}

TEST(TestUnsortedTableM, erase_no_throw) {
    UnsortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    table.erase(1);
    table.erase(3);
    EXPECT_TRUE(table.is_empty());
    std::cout << table;
}

TEST(TestUnsortedTableM, erase_throw) {
    UnsortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(25, "twenty five");
    EXPECT_FALSE(table.is_empty());
    EXPECT_ANY_THROW(table.erase(4));
    table.erase(1);
    table.erase(25);
    EXPECT_TRUE(table.is_empty());
    EXPECT_ANY_THROW(table.erase(1));
    std::cout << table;
}

TEST(TestUnsortedTableM, found_no_throw) {
    UnsortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.found(2), "two");
}

TEST(TestUnsortedTableM, found_throw) {
    UnsortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    EXPECT_ANY_THROW(table.found(18));
}

TEST(TestUnsortedTableM, is_empty) {
    UnsortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(777, "luck");
    EXPECT_FALSE(table.is_empty());
}
