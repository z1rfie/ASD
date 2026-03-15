#include <gtest/gtest.h>
#include "../lib_tree/tree.h"

TEST(TestTree, default_constructor) {
    Tree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());
}

TEST(TestTree, test_insert) {
    Tree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(1, "one");
    EXPECT_FALSE(t.is_empty());

    EXPECT_EQ(*t.find(8), "eight");
    EXPECT_EQ(*t.find(2), "two");
    EXPECT_EQ(*t.find(5), "five");
    EXPECT_EQ(*t.find(1), "one");
}

TEST(TestTree, test_find) {
    Tree<std::string, int> t;
    EXPECT_TRUE(t.is_empty());

    t.insert("one", 1);
    t.insert("abs", 125);
    EXPECT_FALSE(t.is_empty());

    EXPECT_EQ(*t.find("one"), 1);
    EXPECT_EQ(*t.find("abs"), 125);
}

TEST(TestTree, test_find_empty) {
    Tree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    EXPECT_EQ(t.find(777), nullptr);
}

TEST(TestTree, test_not_found) {
    Tree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(1, "one");
    EXPECT_FALSE(t.is_empty());

    EXPECT_EQ(t.find(777), nullptr);
}

TEST(TestTree, erase) {
    Tree<int, std::string> t;
    t.insert(8, "eight");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(1, "one");

    t.erase(2);

    EXPECT_EQ(t.find(2), nullptr);
    EXPECT_EQ(*t.find(1), "one");
    EXPECT_EQ(*t.find(8), "eight");
    EXPECT_EQ(*t.find(5), "five");
}

TEST(TestTree, erase_nonexistent) {
    Tree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(1, "one");

    t.erase(777);

    EXPECT_EQ(*t.find(8), "eight");
    EXPECT_EQ(*t.find(2), "two");
    EXPECT_EQ(*t.find(5), "five");
    EXPECT_EQ(*t.find(1), "one");
}

TEST(TestTree, erase_single_node) {
    Tree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");
    t.erase(8);

    EXPECT_TRUE(t.is_empty());
    EXPECT_EQ(t.find(8), nullptr);
}

TEST(TestTree, erase_all) {
    Tree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(1, "one");

    t.erase(8);
    t.erase(2);
    t.erase(5);
    t.erase(1);

    EXPECT_TRUE(t.is_empty());
}

TEST(TestTree, clear) {
    Tree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(1, "one");
    EXPECT_FALSE(t.is_empty());

    t.clear();
    EXPECT_TRUE(t.is_empty());
}

TEST(TestTree, is_empty) {
    Tree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");

    EXPECT_FALSE(t.is_empty());

    t.erase(8);

    EXPECT_TRUE(t.is_empty());
}

TEST(TestTree, print_w) {
    Tree<int, std::string> t;

    t.insert(8, "eight");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(1, "one");
    t.insert(3, "three");
    t.insert(4, "four");

    t.print_w();
}

TEST(TestTree, print_DLCR) {
    Tree<int, std::string> t;

    t.insert(1, "один");
    t.insert(2, "два");
    t.insert(3, "три");
    t.insert(4, "четыре");
    t.insert(5, "пять");
    t.insert(6, "шесть");
    t.insert(7, "семь");
    t.insert(8, "восемь");
    t.insert(9, "девять");
    t.insert(10, "десять");
    t.insert(11, "одиннадцать");

    t.print_DLCR();
}

TEST(TestTree, print_DLRC) {
    Tree<int, std::string> t;

    t.insert(1, "один");
    t.insert(2, "два");
    t.insert(3, "три");
    t.insert(4, "четыре");
    t.insert(5, "пять");
    t.insert(6, "шесть");
    t.insert(7, "семь");
    t.insert(8, "восемь");
    t.insert(9, "девять");
    t.insert(10, "десять");
    t.insert(11, "одиннадцать");

    t.print_DLRC();
}

TEST(TestTree, print_DCLR) {
    Tree<int, std::string> t;

    t.insert(1, "один");
    t.insert(2, "два");
    t.insert(3, "три");
    t.insert(4, "четыре");
    t.insert(5, "пять");
    t.insert(6, "шесть");
    t.insert(7, "семь");
    t.insert(8, "восемь");
    t.insert(9, "девять");
    t.insert(10, "десять");
    t.insert(11, "одиннадцать");

    t.print_DCLR();
}