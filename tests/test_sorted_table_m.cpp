#include <gtest/gtest.h>
#include "../lib_sorted_table_m/sorted_table_m.h"

TEST(TestSortedTableM, init_table) {
    SortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableM, insert_no_throw) {
    SortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(100, "one");
    table.insert(150, "two");
    table.insert(50, "three");
    EXPECT_FALSE(table.is_empty()); // [] скобки
}

TEST(TestSortedTableM, insert_throw) {
    SortedTableM<std::string, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert("abc", "one");
    table.insert("le", "two");
    table.insert("third", "three");
    std::cout << table;
    EXPECT_FALSE(table.is_empty());
    EXPECT_ANY_THROW(table.insert("le", "second"));
}

TEST(TestSortedTableM, erase_no_throw) {
    SortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    table.erase(1);
    table.erase(3);
    EXPECT_TRUE(table.is_empty());
    std::cout << table;
}

TEST(TestSortedTableM, erase_throw) {
    SortedTableM<int, std::string> table;
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

TEST(TestSortedTableM, found_no_throw) {
    SortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.found(2), "two");
}

TEST(TestSortedTableM, found_throw) {
    SortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    EXPECT_FALSE(table.is_empty());
    EXPECT_ANY_THROW(table.found(18));
}

TEST(TestSortedTableM, is_empty) {
    SortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(777, "luck");
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableM, insert_after_delete) {
    SortedTableM<int, std::string> table;
    
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    std::cout << table << std::endl;

    table.erase(2);
    std::cout << table << std::endl;

    table.insert(18, "luck");
    std::cout << table << std::endl;

    table.insert(123, "abc");
    std::cout << table << std::endl;
}
