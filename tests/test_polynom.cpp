#include <gtest/gtest.h>
#include <sstream>
#include "polynom.h"

TEST(TestPolynom, default_constructor) {
    Polynom p;
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynom, constructor_from_monom) {
    int powers[3] = { 2, 1, 0 };
    Monom m(3.5, powers);
    Polynom p(m);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "3.5x^2y");
}

TEST(TestPolynom, copy_constructor) {
    int powers[3] = { 2, 1, 0 };
    Monom m(3.5, powers);
    Polynom p1(m);
    Polynom p2(p1);
    std::stringstream ss1, ss2;
    ss1 << p1;
    ss2 << p2;
    EXPECT_EQ(ss1.str(), ss2.str());
}

TEST(TestPolynom, constructor_from_string) {
    Polynom p("x^2 + 2xy + y^2");
    EXPECT_DOUBLE_EQ(p.calculate_value_point(2, 3, 1), 25.0);
}

TEST(TestPolynom, constructor_from_string_negative) {
    Polynom p("-x^2 - 2xy - y^2");
    EXPECT_DOUBLE_EQ(p.calculate_value_point(2, 3, 1), -25.0);
}

TEST(TestPolynom, constructor_from_string_sorted) {
    Polynom p("y^2 + x^2 + xy");
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "1x^2 + 1xy + 1y^2");
}

TEST(TestPolynom, assignment) {
    int powers[3] = { 2, 1, 0 };
    Monom m(3.5, powers);
    Polynom p1(m);
    Polynom p2;
    p2 = p1;
    std::stringstream ss1, ss2;
    ss1 << p1;
    ss2 << p2;
    EXPECT_EQ(ss1.str(), ss2.str());
}

TEST(TestPolynom, self_assignment) {
    int powers[3] = { 2, 1, 0 };
    Monom m(3.5, powers);
    Polynom p(m);
    std::stringstream ss1;
    ss1 << p;
    p = p;
    std::stringstream ss2;
    ss2 << p;
    EXPECT_EQ(ss1.str(), ss2.str());
}

TEST(TestPolynom, add_monom) {
    Polynom p("x^2 + y^2");
    int powers[3] = { 0, 0, 1 };
    Monom m(3.0, powers);
    Polynom result = p + m;
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 4), 25.0);
}

TEST(TestPolynom, add_monom_sorted_order) {
    int p1[3] = { 0, 2, 0 }; 
    int p2[3] = { 2, 0, 0 };  
    int p3[3] = { 0, 0, 0 };

    Polynom p;
    p += Monom(2.0, p1);
    p += Monom(2.0, p2);
    p += Monom(1.0, p3);

    int p4[3] = { 1, 1, 0 };
    Monom m(2.0, p4);

    Polynom result = p + m;

    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "2x^2 + 2xy + 2y^2 + 1");
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 1), 39.0);
}

TEST(TestPolynom, add_polynom) {
    Polynom p1("x^2 + y^2");
    Polynom p2("2xy + z");
    Polynom result = p1 + p2;
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 4), 29.0);
}

TEST(TestPolynom, add_similar_terms) {
    Polynom p("x^2 + 2x^2");
    EXPECT_DOUBLE_EQ(p.calculate_value_point(2, 1, 1), 12.0);
}

TEST(TestPolynom, add_cancel_terms) {
    Polynom p("x^2 + 2xy");
    int powers[3] = { 2, 0, 0 };
    Monom m(-1.0, powers);
    p += m;
    EXPECT_DOUBLE_EQ(p.calculate_value_point(2, 3, 1), 12.0); 
}

TEST(TestPolynom, monom_plus_polynom) {
    int powers[3] = { 1, 0, 0 };
    Monom m(2.0, powers);
    Polynom p("3y + 1");
    Polynom result = m + p;
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 1), 14.0);
}

TEST(TestPolynom, sub_monom) {
    Polynom p("x^2 + y^2 + z");
    int powers[3] = { 0, 0, 1 };
    Monom m(1.0, powers);
    Polynom result = p - m;
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 4), 13.0);
}

TEST(TestPolynom, sub_polynom) {
    Polynom p1("x^2 + y^2 + z");
    Polynom p2("y^2 + z");
    Polynom result = p1 - p2;
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 4), 4.0);
}

TEST(TestPolynom, sub_to_zero) {
    Polynom p1("3x^2y");
    Polynom p2("3x^2y");
    Polynom result = p1 - p2;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynom, monom_minus_polynom) {
    int powers[3] = { 2, 0, 0 };
    Monom m(5.0, powers);
    Polynom p("2x^2 + y");
    Polynom result = m - p;
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 1), 9.0); 
}

TEST(TestPolynom, mul_monom) {
    Polynom p("x^2 + y^2");
    int powers[3] = { 0, 0, 1 };
    Monom m(2.0, powers);
    Polynom result = p * m;
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 4), 104.0);
}

TEST(TestPolynom, mul_polynom) {
    Polynom p1("x + y");
    Polynom p2("x - y");
    Polynom result = p1 * p2;
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 1), -5.0); 
}

TEST(TestPolynom, mul_sorted_after_multiply) {
    Polynom p1("x + y");
    Polynom p2("x + y");
    Polynom result = p1 * p2;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "1x^2 + 2xy + 1y^2");
}

TEST(TestPolynom, monom_mul_polynom) {
    int powers[3] = { 1, 0, 0 };
    Monom m(2.0, powers);
    Polynom p("x + y");
    Polynom result = m * p;
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 1), 20.0); 
}

TEST(TestPolynom, div_monom) {
    Polynom p("2x^2y + 4xy^2");
    int powers[3] = { 1, 1, 0 };
    Monom m(2.0, powers);
    Polynom result = p / m;
    EXPECT_DOUBLE_EQ(result.calculate_value_point(2, 3, 1), 8.0); 
}

TEST(TestPolynom, div_monom_negative_power_throws) {
    Polynom p("x^2 + y");
    int powers[3] = { 2, 0, 0 };
    Monom m(1.0, powers);
    EXPECT_THROW(p / m, std::invalid_argument);
}

TEST(TestPolynom, calculate_value_point) {
    Polynom p("x^2y + 2xyz - 3z^2");
    EXPECT_DOUBLE_EQ(p.calculate_value_point(2, 3, 1), 12 + 12 - 3);
    EXPECT_DOUBLE_EQ(p.calculate_value_point(1, 1, 1), 0.0);
    EXPECT_DOUBLE_EQ(p.calculate_value_point(0, 5, 2), -12.0);
}

TEST(TestPolynom, sorted_order) {
    int p1[3] = { 2, 0, 0 };
    int p2[3] = { 1, 1, 0 };
    int p3[3] = { 0, 2, 0 };
    int p4[3] = { 0, 0, 0 };

    Polynom p(Monom(2.0, p3));
    p += Monom(2.0, p1);
    p += Monom(1.0, p4);
    p += Monom(2.0, p2);

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "2x^2 + 2xy + 2y^2 + 1");
}

TEST(TestPolynom, remove_zero_terms) {
    Polynom p("x^2 + 2x^2 - 3x^2");
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "0");
}

TEST(TestPolynom, add_zero_monom) {
    Polynom p("x^2 + y^2");
    Monom zero;
    Polynom result = p + zero;
    std::stringstream ss1, ss2;
    ss1 << p;
    ss2 << result;
    EXPECT_EQ(ss1.str(), ss2.str());
}

TEST(TestPolynom, output_contains_all_terms) {
    Polynom p("x^2 + 2xy + y^2");
    std::stringstream ss;
    ss << p;
    std::string output = ss.str();
    EXPECT_TRUE(output.find("x^2") != std::string::npos);
    EXPECT_TRUE(output.find("xy") != std::string::npos);
    EXPECT_TRUE(output.find("y^2") != std::string::npos);
}

TEST(TestPolynom, output_negative_coefficient) {
    Polynom p("3x^2 - 2y + 1");
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "3x^2 - 2y + 1");
}

TEST(TestPolynom, output_all_negative) {
    Polynom p("-3x^2 - 2y - 1");
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "-3x^2 - 2y - 1");
}

TEST(TestPolynom, output_single_monom) {
    int powers[3] = { 2, 1, 0 };
    Monom m(3.5, powers);
    Polynom p(m);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "3.5x^2y");
}

TEST(TestPolynom, output_zero) {
    Polynom p("3x^2 - 3x^2");
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "0");
}