#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

#define EPSILON 0.000001

TEST(TestCircleLib, create_circle_default_constructor) {
    // Act & Assert
    ASSERT_NO_THROW(Circle c);
}

TEST(TestCircleLib, check_circle_default_constructor) {
    // Arrange
    Circle c;

    // Act
    Circle actual_result = c;

    // Assert
    Circle expected_result = Circle(Point(0, 0),1);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircleLib, create_circle_init_constructor) {
    // Arrange
    Point center(3,5);
    float r = 10;

    // Act & Assert
    ASSERT_NO_THROW(Circle(center, r));
}

TEST(TestCircleLib, check_circle_init_constructor) {
    // Arrange
    Point center(3, 5);
    float r = 10;
    Circle c(center, r);

    // Act
    Circle actual_result = c;

    // Assert
    Circle expected_result = Circle(Point(3, 5), 10);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircleLib, throw_circle_init_constructor) {
    // Arrange
    Point center(3, 5);
    float r = -8;

    // Act & Assert
    EXPECT_THROW(Circle c(center, r), std::invalid_argument);
}

TEST(TestCircleLib, circle_copy_constructor) {
    // Arrange
    Circle circle(Point(4,5), 7);
    Circle circle_copy(circle);

    // Act
    Circle actual_result = circle_copy;

    // Assert
    Circle expected_result = Circle(Point(4, 5), 7);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircleLib, circle_comparison_operator) {
    // Arrange
    Circle c1(Point(4, 5), 6);
    Circle c2(c1);

    // Act
    bool actual_result = (c1 == c2);

    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircleLib, circle_comparison_operator_false) {
    // Arrange
    float x = 6;
    float y = 2;
    float r = 5;
    Circle c1(Point(x, y), r);
    Circle c2(Point(4, 5), 6);

    // Act
    bool actual_result = (c1 == c2);

    // Assert
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}

