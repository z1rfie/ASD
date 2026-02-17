#include <gtest/gtest.h>
#include "../lib_unsorted_table_l/unsorted_table_l.h"

TEST(TestUnsortedTableL, init_table) {
    UnsortedTableL<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableL, insert_no_throw) {
    UnsortedTableL<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    std::cout << table;
}

TEST(TestUnsortedTableL, insert_throw) {
    UnsortedTableL<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    EXPECT_ANY_THROW(table.insert(2, "second"));
    std::cout << table;
}

TEST(TestUnsortedTableL, erase_no_throw) {
    UnsortedTableL<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    table.erase(1);
    table.erase(3);
    EXPECT_TRUE(table.is_empty());
    std::cout << table;
}

TEST(TestUnsortedTableL, erase_throw) {
    UnsortedTableL<int, std::string> table;
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

TEST(TestUnsortedTableL, found_no_throw) {
    UnsortedTableL<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.found(2), "two");
}

TEST(TestUnsortedTableL, found_throw) {
    UnsortedTableL<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    EXPECT_ANY_THROW(table.found(18));
}

TEST(TestUnsortedTableL, is_empty) {
    UnsortedTableL<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(777, "luck");
    EXPECT_FALSE(table.is_empty());
}

TEST(TestUnsortedTableL, insert_after_delete) {
    UnsortedTableL<int, std::string> table;
    
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    std::cout << table << std::endl;

    table.erase(2);
    std::cout << table << std::endl;

    table.insert(777, "luck");
    std::cout << table << std::endl;

    table.insert(123, "abc");
    std::cout << table << std::endl;
}
