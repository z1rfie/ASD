#include <gtest/gtest.h>
#include "../lib_bst/bst.h"

TEST(TestBST, insert_and_print) {
	BSTree<int, std::string> t;

	for (int i = 0; i < 10; i++) {
		try {
			t.insert(1 + rand() % 10, "lalala");
		}
		catch (const std::logic_error& e) {
			i--;
		}
	}

	t.print_DLCR();
}

TEST(TestBST, default_constructor) {
    BSTree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());
}

TEST(TestBST, test_insert) {
    BSTree<int, std::string> t;
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

TEST(TestBST, test_find) {
    BSTree<std::string, int> t;
    EXPECT_TRUE(t.is_empty());

    t.insert("one", 1);
    t.insert("abs", 125);
    EXPECT_FALSE(t.is_empty());

    EXPECT_EQ(*t.find("one"), 1);
    EXPECT_EQ(*t.find("abs"), 125);
}

TEST(TestBST, test_find_empty) {
    BSTree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    EXPECT_EQ(t.find(777), nullptr);
}

TEST(TestBST, test_not_found) {
    BSTree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(1, "one");
    EXPECT_FALSE(t.is_empty());

    EXPECT_EQ(t.find(777), nullptr);
}

TEST(TestBST, erase) {
    BSTree<int, std::string> t;
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

TEST(TestBST, erase_nonexistent) {
    BSTree<int, std::string> t;
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

TEST(TestBST, erase_single_node) {
    BSTree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");
    t.erase(8);

    EXPECT_TRUE(t.is_empty());
    EXPECT_EQ(t.find(8), nullptr);
}

TEST(TestBST, erase_all) {
    BSTree<int, std::string> t;
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

TEST(TestBST, clear) {
    BSTree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");
    t.insert(2, "two");
    t.insert(5, "five");
    t.insert(1, "one");
    EXPECT_FALSE(t.is_empty());

    t.clear();
    EXPECT_TRUE(t.is_empty());
}

TEST(TestBST, is_empty) {
    BSTree<int, std::string> t;
    EXPECT_TRUE(t.is_empty());

    t.insert(8, "eight");

    EXPECT_FALSE(t.is_empty());

    t.erase(8);

    EXPECT_TRUE(t.is_empty());
}