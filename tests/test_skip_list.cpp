#include <windows.h>
#include <iostream>
#include "skip_list.h"
#include <gtest/gtest.h>

TEST(TestSkipList, test_print) {
    SkipList<int, std::string> s_list(6);
    s_list.insert(1, "one");
    s_list.insert(9, "nine");
    s_list.insert(7, "seven");
    s_list.insert(15, "fifteen");

    s_list.print();
}