#include <windows.h>
#include <iostream>
#include "skip_list.h"
#include <gtest/gtest.h>

TEST(TestSkipList, test_print_1) {
    SkipList<int, std::string> s_list(6);
    s_list.insert(1, "one");
    s_list.insert(9, "nine");
    s_list.insert(7, "seven");
    s_list.insert(15, "fifteen");

    s_list.print();
}

//TEST(TestSkipList, test_print_2) {
//    SkipList<std::string, std::string> s_list(5);
//    s_list.insert("abc", "one");
//    s_list.insert("lala", "nine");
//    s_list.insert("lp", "seven");
//    s_list.insert("emo", "fifteen");
//
//    s_list.print();
//}