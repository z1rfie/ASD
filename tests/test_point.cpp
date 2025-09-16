#include <gtest/gtest.h>
#include "../lib_point/point.h"

#define EPSILON 0.000001

TEST(TestPointLib, create_point_default_constructor) {
    // Act & Assert
    ASSERT_NO_THROW(Point p);
}

TEST(TestPointLib, check_point_default_constructor) {
    // Arrange
    Point p;

    // Act
    Point actual_result = p;

    // Assert
    Point expected_result = Point(0, 0);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, create_point_init_constructor) {
    // Arrange
    float x = 10;
    float y = 2;

    // Act & Assert
    ASSERT_NO_THROW(Point(x, y));
}

TEST(TestPointLib, check_point_init_constructor) {
    // Arrange
    Point p(3,4);

    // Act
    Point actual_result = p;

    // Assert
    Point expected_result = Point(3, 4);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, point_copy_constructor) {
    // Arrange
    float x = 6;
    float y = 2;
    Point p1(x, y);
    Point p2(p1);

    // Act
    Point actual_result = p2;

    // Assert
    Point expected_result = Point(6,2);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, point_comparison_operator) {
    // Arrange
    float x = 6;
    float y = 2;
    Point p1(x, y);
    Point p2(p1);

    // Act
    bool actual_result = (p1 == p2); 

    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, point_comparison_operator_false) {
    // Arrange
    float x = 6;
    float y = 2;
    Point p1(x, y);
    Point p2(3,4);

    // Act
    bool actual_result = (p1 == p2);

    // Assert
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, distance_between_points) {
    // Arrange
    Point p1(6, 2);
    Point p2(3, 6);

    // Act
    float distance = p1.distance_between_points(p2);

    // Assert
    EXPECT_FLOAT_EQ(5.0, distance);
}

TEST(TestPointLib, distance_between_points_negative_coords) {
    // Arrange
    Point p1(-2, -1);
    Point p2(1, 3);

    // Act
    float distance = p1.distance_between_points(p2);

    // Assert
    EXPECT_FLOAT_EQ(5.0, distance); 
}
