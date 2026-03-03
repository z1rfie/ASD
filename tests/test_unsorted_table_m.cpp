#include <gtest/gtest.h>
#include "../lib_unsorted_table_m/unsorted_table_m.h"

TEST(TestUnsortedTableM, init_table) {
    UnsortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableM, insert_no_throw) {
    UnsortedTableM<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table[1], "one");
    EXPECT_EQ(table[2], "two");
    EXPECT_EQ(table[3], "three");
}

TEST(TestUnsortedTableM, insert_throw) {
    UnsortedTableM<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_ANY_THROW(table.insert(2, "second"));

    EXPECT_EQ(table[1], "one");
    EXPECT_EQ(table[2], "two");
}

TEST(TestUnsortedTableM, erase_no_throw) {
    UnsortedTableM<int, std::string> table;

    table.insert(1, "one");
    table.insert(3, "three");

    table.erase(1);
    table.erase(3);

    EXPECT_TRUE(table.is_empty());

    EXPECT_ANY_THROW(table.found(1));
    EXPECT_ANY_THROW(table.found(3));
}

TEST(TestUnsortedTableM, erase_throw) {
    UnsortedTableM<int, std::string> table;

    table.insert(1, "one");
    table.insert(25, "twenty five");

    EXPECT_ANY_THROW(table.erase(4));

    EXPECT_EQ(table[1], "one");
    EXPECT_EQ(table[25], "twenty five");

    table.erase(1);
    table.erase(25);

    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableM, found_no_throw) {
    UnsortedTableM<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table[2], "two");
}

TEST(TestUnsortedTableM, found_throw) {
    UnsortedTableM<int, std::string> table;

    table.insert(1, "one");

    EXPECT_ANY_THROW(table.found(18));
}

TEST(TestUnsortedTableM, is_empty) {
    UnsortedTableM<int, std::string> table;

    EXPECT_TRUE(table.is_empty());

    table.insert(777, "luck");

    EXPECT_FALSE(table.is_empty());
}

TEST(TestUnsortedTableM, insert_after_delete) {
    UnsortedTableM<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    table.erase(2);
    EXPECT_ANY_THROW(table.found(2));

    table.insert(777, "luck");
    EXPECT_EQ(table[777], "luck");

    table.insert(123, "abc");
    EXPECT_EQ(table[123], "abc");

    EXPECT_EQ(table[1], "one");
    EXPECT_EQ(table[3], "three");
}

TEST(TestUnsortedTableM, square_bracket_operator) {
    UnsortedTableM<int, std::string> table;

    ASSERT_TRUE(table.is_empty());

    std::string& value = table[42];

    ASSERT_FALSE(table.is_empty());

    ASSERT_EQ(value, "");
    ASSERT_EQ(table[42], "");

    table[42] = "answer";

    ASSERT_EQ(table[42], "answer");

    table[100] = "hundred";

    ASSERT_EQ(table[42], "answer");
    ASSERT_EQ(table[100], "hundred");

    std::string& new_value = table[999];
    ASSERT_EQ(new_value, "");
    ASSERT_EQ(table[999], "");
}