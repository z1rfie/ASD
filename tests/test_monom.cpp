#include <gtest/gtest.h>
#include "monom.h"

TEST(TestMonom, default_constructor) {
    Monom m;
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "0");
    EXPECT_DOUBLE_EQ(m.calculate_value_point_monom(2, 3, 4), 0.0);
}

TEST(TestMonom, constructor_with_coefficient) {
    Monom m(5.0);
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "5");
    EXPECT_DOUBLE_EQ(m.calculate_value_point_monom(2, 3, 4), 5.0);
}

TEST(TestMonom, constructor_with_powers) {
    int powers[3] = { 2, 1, 3 };
    Monom m(3.5, powers);
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "3.5x^2yz^3");
    EXPECT_DOUBLE_EQ(m.calculate_value_point_monom(2, 3, 4), 2688.0);
}

TEST(TestMonom, copy_constructor) {
    int powers[3] = { 2, 1, 0 };
    Monom m1(3.5, powers);
    Monom m2(m1);
    std::stringstream ss;
    ss << m2;
    EXPECT_EQ(ss.str(), "3.5x^2y");
    EXPECT_DOUBLE_EQ(m2.calculate_value_point_monom(2, 3, 4), 42.0);
}

TEST(TestMonom, equality_operator) {
    int p1[3] = { 2, 1, 0 };
    int p2[3] = { 2, 1, 0 };
    int p3[3] = { 1, 1, 1 };
    Monom m1(5.0, p1);
    Monom m2(3.0, p2);
    Monom m3(5.0, p3);
    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
}

TEST(TestMonom, inequality_operator) {
    int p1[3] = { 2, 1, 0 };
    int p2[3] = { 2, 1, 0 };
    int p3[3] = { 1, 1, 1 };
    Monom m1(5.0, p1);
    Monom m2(3.0, p2);
    Monom m3(5.0, p3);
    EXPECT_FALSE(m1 != m2);
    EXPECT_TRUE(m1 != m3);
}

TEST(TestMonom, greater_than_operator) {
    int p1[3] = { 3, 0, 0 };
    int p2[3] = { 2, 1, 0 };
    int p3[3] = { 2, 0, 1 };
    int p4[3] = { 2, 1, 0 };
    Monom m1(1.0, p1);
    Monom m2(1.0, p2);
    Monom m3(1.0, p3);
    Monom m4(1.0, p4);
    EXPECT_TRUE(m1 > m2);
    EXPECT_TRUE(m2 > m3);
    EXPECT_FALSE(m2 > m4);
    EXPECT_FALSE(m1 > m1);
}

TEST(TestMonom, less_than_operator) {
    int p1[3] = { 2, 1, 0 };
    int p2[3] = { 1, 2, 0 };
    Monom m1(1.0, p1);
    Monom m2(1.0, p2);
    EXPECT_TRUE(m2 < m1);
    EXPECT_FALSE(m1 < m2);
}

TEST(TestMonom, addition) {
    int p[3] = { 2, 1, 0 };
    Monom m1(5.0, p);
    Monom m2(3.0, p);
    Monom sum = m1 + m2;
    std::stringstream ss;
    ss << sum;
    EXPECT_EQ(ss.str(), "8x^2y");
    EXPECT_DOUBLE_EQ(sum.calculate_value_point_monom(2, 3, 4), 96.0);

    int p2[3] = { 1, 1, 1 };
    Monom m3(5.0, p2);
    EXPECT_THROW(m1 + m3, std::invalid_argument);
}

TEST(TestMonom, addition_assignment) {
    int p[3] = { 2, 1, 0 };
    Monom m1(5.0, p);
    Monom m2(3.0, p);
    m1 += m2;
    std::stringstream ss;
    ss << m1;
    EXPECT_EQ(ss.str(), "8x^2y");
    EXPECT_DOUBLE_EQ(m1.calculate_value_point_monom(2, 3, 4), 96.0);
}

TEST(TestMonom, subtraction) {
    int p[3] = { 2, 1, 0 };
    Monom m1(5.0, p);
    Monom m2(3.0, p);
    Monom diff = m1 - m2;
    std::stringstream ss;
    ss << diff;
    EXPECT_EQ(ss.str(), "2x^2y");

    int p2[3] = { 1, 1, 1 };
    Monom m3(4.0, p2);

    EXPECT_DOUBLE_EQ(diff.calculate_value_point_monom(2, 3, 4), 24.0);
    EXPECT_THROW(m1 + m3, std::invalid_argument);
}

TEST(TestMonom, unary_minus) {
    int p[3] = { 2, 1, 0 };
    Monom m(5.0, p);
    Monom neg = -m;
    std::stringstream ss;
    ss << neg;
    EXPECT_EQ(ss.str(), "-5x^2y");
    EXPECT_DOUBLE_EQ(neg.calculate_value_point_monom(2, 3, 4), -60.0);
}

TEST(TestMonom, multiplication) {
    int p1[3] = { 2, 1, 0 };
    int p2[3] = { 1, 0, 2 };
    Monom m1(5.0, p1);
    Monom m2(3.0, p2);
    Monom prod = m1 * m2;
    std::stringstream ss;
    ss << prod;
    EXPECT_EQ(ss.str(), "15x^3yz^2");
    EXPECT_DOUBLE_EQ(prod.calculate_value_point_monom(2, 3, 4), 5760.0);
}

TEST(TestMonom, multiplication_by_scalar) {
    int p[3] = { 2, 1, 0 };
    Monom m(5.0, p);
    Monom prod = m * 2.5;
    std::stringstream ss;
    ss << prod;
    EXPECT_EQ(ss.str(), "12.5x^2y");
    EXPECT_DOUBLE_EQ(prod.calculate_value_point_monom(2, 3, 4), 150.0);
}

TEST(TestMonom, multiplication_assignment) {
    int p1[3] = { 2, 1, 0 };
    int p2[3] = { 1, 0, 2 };
    Monom m1(5.0, p1);
    Monom m2(3.0, p2);
    m1 *= m2;
    std::stringstream ss;
    ss << m1;
    EXPECT_EQ(ss.str(), "15x^3yz^2");
    EXPECT_DOUBLE_EQ(m1.calculate_value_point_monom(2, 3, 4), 5760.0);
}

TEST(TestMonom, multiply_by_zero_monom) {
    int p[3] = { 2, 1, 0 };
    Monom m1(5.0, p);
    Monom m2(0.0, p);  

    Monom prod = m1 * m2;
    EXPECT_DOUBLE_EQ(prod.get_coefficient(), 0.0);
}

TEST(TestMonom, division) {
    int p1[3] = { 3, 2, 1 };
    int p2[3] = { 1, 1, 1 };
    Monom m1(10.0, p1);
    Monom m2(2.0, p2);
    Monom quot = m1 / m2;
    std::stringstream ss;
    ss << quot;
    EXPECT_EQ(ss.str(), "5x^2y");
    EXPECT_DOUBLE_EQ(quot.calculate_value_point_monom(2, 3, 4), 60.0);
}

TEST(TestMonom, division_by_zero_throws) {
    int p[3] = { 2, 1, 0 };
    Monom m1(5.0, p);
    Monom m2(0.0, p);
    EXPECT_THROW(m1 / m2, std::invalid_argument);
}

TEST(TestMonom, division_negative_power_throws) {
    int p1[3] = { 1, 1, 0 };
    int p2[3] = { 2, 0, 0 };
    Monom m1(5.0, p1);
    Monom m2(2.0, p2);
    EXPECT_THROW(m1 / m2, std::invalid_argument);
}

TEST(TestMonom, division_by_scalar) {
    int p[3] = { 2, 1, 0 };
    Monom m(10.0, p);
    Monom quot = m / 2.0;
    std::stringstream ss;
    ss << quot;
    EXPECT_EQ(ss.str(), "5x^2y");
    EXPECT_DOUBLE_EQ(quot.calculate_value_point_monom(2, 3, 4), 60.0);
}

TEST(TestMonom, division_assignment) {
    int p1[3] = { 3, 2, 1 };
    int p2[3] = { 1, 1, 1 };
    Monom m1(10.0, p1);
    Monom m2(2.0, p2);
    m1 /= m2;
    std::stringstream ss;
    ss << m1;
    EXPECT_EQ(ss.str(), "5x^2y");
    EXPECT_DOUBLE_EQ(m1.calculate_value_point_monom(2, 3, 4), 60.0);
}

TEST(TestMonom, calculate_value_point) {
    int powers[3] = { 2, 1, 3 };
    Monom m(3.5, powers);
    EXPECT_DOUBLE_EQ(m.calculate_value_point_monom(2, 3, 4), 2688.0);

    Monom c(5.0);
    EXPECT_DOUBLE_EQ(c.calculate_value_point_monom(100, 200, 300), 5.0);

    int px[3] = { 3, 0, 0 };
    Monom mx(2.0, px);
    EXPECT_DOUBLE_EQ(mx.calculate_value_point_monom(5, 0, 0), 250.0);
}

TEST(TestMonom, assignment_operator) {
    int p[3] = { 2, 1, 0 };
    Monom m1(5.0, p);
    Monom m2;
    m2 = m1;
    std::stringstream ss;
    ss << m2;
    EXPECT_EQ(ss.str(), "5x^2y");
    EXPECT_DOUBLE_EQ(m2.calculate_value_point_monom(2, 3, 4), 60.0);
    m2 = m2;
    EXPECT_DOUBLE_EQ(m2.calculate_value_point_monom(2, 3, 4), 60.0);
}