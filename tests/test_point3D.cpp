#include <gtest/gtest.h>
#include "../lib_point3D/point3D.h"

#define EPSILON 0.000001

TEST(TestPoint3DLib, create_point3D_default_constructor) {
    // Act & Assert
    ASSERT_NO_THROW(Point3D p);
}

TEST(TestPoint3DLib, check_point3D_default_constructor) {
    // Arrange
    Point3D p;

    // Act
    Point3D actual_result = p;

    // Assert
    Point expected_result = Point3D(0, 0, 0);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, create_point3D_init_constructor) {
    // Arrange
    float x = 10;
    float y = 2;
    float z = -3;

    // Act & Assert
    ASSERT_NO_THROW(Point3D(x, y, z));
}

TEST(TestPoint3DLib, check_point3D_init_constructor) {
    // Arrange
    Point3D p(3, 4, 5);

    // Act
    Point actual_result = p;

    // Assert
    Point expected_result = Point3D(3, 4, 5);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, point3D_copy_constructor) {
    // Arrange
    float x = 6;
    float y = 2;
    float z = 4;
    Point3D p1(x, y, z);
    Point3D p2(p1);

    // Act
    Point actual_result = p2;

    // Assert
    Point expected_result = Point3D(6, 2, 4);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, point3D_comparison_operator) {
    // Arrange
    float x = 6;
    float y = 2;
    float z = 4;
    Point3D p1(x, y, z);
    Point3D p2(p1);

    // Act
    bool actual_result = (p1 == p2);

    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, point3D_comparison_operator_false) {
    // Arrange
    float x = 6;
    float y = 2;
    float z = 4;
    Point3D p1(x, y, z);
    Point3D p2(3, 4, 0);

    // Act
    bool actual_result = (p1 == p2);

    // Assert
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, distance_between_points3D) {
    // Arrange
    Point3D p1(6, 2, 0);    
    Point3D p2(3, 6, 0);   

    // Act
    float distance = p1.distance_between_points(p2);

    // Assert 
    EXPECT_FLOAT_EQ(5.0, distance);
}

TEST(TestPoint3DLib, distance_between_points3D_negative_coords) {
    // Arrange
    Point3D p1(-2, -1, 0);
    Point3D p2(1, 3, 0);  

    // Act
    float distance = p1.distance_between_points(p2);

    // Assert 
    EXPECT_FLOAT_EQ(5.0, distance);
}