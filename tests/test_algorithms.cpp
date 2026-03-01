#include <windows.h>
#include <iostream>
#include "algorithms.h"
#include <gtest/gtest.h>

TEST(TestAlgorithmsLib, test_find_local_min) {
    Matrix<int> matr(3, 3);
    matr[0][0] = 7; matr[0][1] = 1; matr[0][2] = 3;
    matr[1][0] = 4; matr[1][1] = 5; matr[1][2] = 6;
    matr[2][0] = 2; matr[2][1] = 8; matr[2][2] = 9;

    EXPECT_EQ(find_local_min(matr, 1, 1), 1);
    EXPECT_EQ(find_local_min(matr, 1, 0), 2);
}

TEST(TestAlgorithmsLib, test_find_local_min_size_4) {
    Matrix<int> matr(4, 4);
    matr[0][0] = 11; matr[0][1] = 15; matr[0][2] = 10; matr[0][3] = 9;
    matr[1][0] = 6;  matr[1][1] = 16; matr[1][2] = 3;  matr[1][3] = 8;
    matr[2][0] = 7;  matr[2][1] = 4;  matr[2][2] = 2;  matr[2][3] = 13;
    matr[3][0] = 14; matr[3][1] = 12; matr[3][2] = 1;  matr[3][3] = 5;

    EXPECT_EQ(find_local_min(matr, 2, 0), 1);
}

TEST(TestAlgorithmsLib, test_find_local_min_different_n_and_m) {
    Matrix<int> matr(2, 3);
    matr[0][0] = 7; matr[0][1] = 1; matr[0][2] = 3;
    matr[1][0] = 4; matr[1][1] = 5; matr[1][2] = 6;

    EXPECT_THROW(find_local_min(matr, 1, 1), std::exception);
}

TEST(TestAlgorithmsLib, test_find_local_min_error_index) {
    Matrix<int> matr(3, 3);
    matr[0][0] = 7; matr[0][1] = 1; matr[0][2] = 3;
    matr[1][0] = 4; matr[1][1] = 5; matr[1][2] = 6;
    matr[2][0] = 2; matr[2][1] = 8; matr[2][2] = 9;

    EXPECT_THROW(find_local_min(matr, 3, 3), std::exception);
}

TEST(TestAlgorithmsLib, test_read_expression) {
    std::string first = "3 * (15 + (x + y) * (2*x - 7*y^2))";
    EXPECT_NO_THROW(read_expression(first));

    std::string second = "3*(15+(x y)*(2*x - 7*y^2))";
    EXPECT_THROW(read_expression(second), std::invalid_argument);

    std::string third = "3*(15+(x+y)*(2*x - 7*y^))";
    EXPECT_THROW(read_expression(third), std::invalid_argument);

    std::string fourth = "3*(15+(x+y)))*(2*x - 7*y^2))";
    EXPECT_THROW(read_expression(fourth), std::invalid_argument);
}

//TEST(TestAlgorithmsLib, test_read_expression_message) {
//    std::string first = "3 * (15 + (x + y) * (2*x - 7*y^2))";
//    EXPECT_NO_THROW(read_expression(first));
//
//    std::string second = "3*(15+(x y)*(2*x - 7*y^2))";
//    try {
//        read_expression(second);
//        FAIL() << "Expected exception for: " << second;
//    }
//    catch (const std::invalid_argument& e) {
//        std::cout << "Exception for '" << second << "': " << e.what() << std::endl;
//        EXPECT_TRUE(std::string(e.what()).find("Missing operation") != std::string::npos);
//    }
//
//    std::string third = "3*(15+(x+y)*(2*x - 7*y^))";
//    try {
//        read_expression(third);
//        FAIL() << "Expected exception for: " << third;
//    }
//    catch (const std::invalid_argument& e) {
//        std::cout << "Exception for '" << third << "': " << e.what() << std::endl;
//        EXPECT_TRUE(std::string(e.what()).find("Missing operand") != std::string::npos);
//    }
//
//    std::string fourth = "3*(15+(x+y)))*(2*x - 7*y^2))";
//    try {
//        read_expression(fourth);
//        FAIL() << "Expected exception for: " << fourth;
//    }
//    catch (const std::invalid_argument& e) {
//        std::cout << "Exception for '" << fourth << "': " << e.what() << std::endl;
//        EXPECT_TRUE(std::string(e.what()).find("Missing opened bracket") != std::string::npos);
//    }
//}

TEST(TestAlgorithmsLib, test_is_looped) {
    List<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }

    Node<int>* node = list.tail();
    node->next = list.head()->next;

    EXPECT_TRUE(is_looped(list));

    node->next = nullptr;
}

TEST(TestAlgorithmsLib, test_is_looped_false) {
    List<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }

    EXPECT_FALSE(is_looped(list));
}

TEST(TestAlgorithmsLib, test_is_looped_reversal_signs) {
    List<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }

    Node<int>* node = list.tail();
    node->next = list.head()->next;

    EXPECT_TRUE(is_looped_reversal_signs(list));

    node->next = nullptr;
}

TEST(TestAlgorithmsLib, test_is_looped_reversal_signs_false) {
    List<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }

    EXPECT_FALSE(is_looped_reversal_signs(list));
}

TEST(TestAlgorithmsLib, test_find_loop) {
    List<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }

    Node<int>* node = list.tail();
    node->next = list.head()->next;

    EXPECT_EQ(find_loop(list), list.head()->next);

    node->next = nullptr;
}

TEST(TestAlgorithmsLib, test_not_find_loop) {
    List<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }

    EXPECT_EQ(find_loop(list), nullptr);
}

TEST(TestAlgorithmsLib, test_count_islands) {
    Matrix<int> matr(4, 4);
    matr[0][0] = 0; matr[0][1] = 1; matr[0][2] = 0; matr[0][3] = 0;
    matr[1][0] = 0; matr[1][1] = 1; matr[1][2] = 0; matr[1][3] = 0;
    matr[2][0] = 1; matr[2][1] = 0; matr[2][2] = 1; matr[2][3] = 1;
    matr[3][0] = 1; matr[3][1] = 0; matr[3][2] = 1; matr[3][3] = 0;

    EXPECT_EQ(return_count_islands(matr), 3);
}

TEST(TestAlgorithmsLib, test_count_islands_one) {
    Matrix<int> matr(4, 4);
    matr[0][0] = 0; matr[0][1] = 0; matr[0][2] = 0; matr[0][3] = 0;
    matr[1][0] = 0; matr[1][1] = 0; matr[1][2] = 0; matr[1][3] = 0;
    matr[2][0] = 1; matr[2][1] = 0; matr[2][2] = 0; matr[2][3] = 0;
    matr[3][0] = 0; matr[3][1] = 0; matr[3][2] = 0; matr[3][3] = 0;

    EXPECT_EQ(return_count_islands(matr), 1);
}


TEST(TestAlgorithmsLib, test_count_islands_null) {
    Matrix<int> matr(4, 4);
    matr[0][0] = 0; matr[0][1] = 0; matr[0][2] = 0; matr[0][3] = 0;
    matr[1][0] = 0; matr[1][1] = 0; matr[1][2] = 0; matr[1][3] = 0;
    matr[2][0] = 0; matr[2][1] = 0; matr[2][2] = 0; matr[2][3] = 0;
    matr[3][0] = 0; matr[3][1] = 0; matr[3][2] = 0; matr[3][3] = 0;

    EXPECT_EQ(return_count_islands(matr), 0);
}

TEST(TestAlgorithmsLib, test_labirint) {
    Matrix<Cell> matr = make_labirint(0, 2, 5, 6);
    print(matr, 5, 6);
}