#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"

#define EPSILON 0.000001

TEST(TestSphereLib, create_sphere_default_constructor) {
    // Act & Assert
    ASSERT_NO_THROW(Sphere s);
}

TEST(TestSphereLib, check_sphere_default_constructor) {
    // Arrange
    Sphere c;

    // Act
    Sphere actual_result = c;

    // Assert
    Sphere expected_result = Sphere(Point3D(0, 0, 0), 1);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereLib, create_sphere_init_constructor) {
    // Arrange
    Point3D center(3, 5, 7);
    float r = 10;

    // Act & Assert
    ASSERT_NO_THROW(Sphere(center, r));
}

TEST(TestSphereLib, check_sphere_init_constructor) {
    // Arrange
    Point3D center(3, 5, 7);
    float r = 10;
    Sphere c(center, r);

    // Act
    Sphere actual_result = c;

    // Assert
    Sphere expected_result = Sphere(Point3D(3, 5, 7), 10);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereLib, throw_sphere_init_constructor) {
    // Arrange
    Point3D center(3, 5, 0);
    float r = -8;

    // Act & Assert
    EXPECT_THROW(Sphere s(center, r), std::invalid_argument);
}

TEST(TestSphereLib, sphere_copy_constructor) {
    // Arrange
    Sphere circle(Point3D(4, 5, 6), 7);
    Sphere circle_copy(circle);

    // Act
    Sphere actual_result = circle_copy;

    // Assert
    Sphere expected_result = Sphere(Point3D(4, 5, 6), 7);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereLib, sphere_comparison_operator) {
    // Arrange
    Sphere c1(Point3D(4.6, 5.2, 0), 6.1);
    Sphere c2(c1);

    // Act
    bool actual_result = (c1 == c2);

    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereLib, sphere_comparison_operator_false) {
    // Arrange
    float x = 6;
    float y = 2;
    float z = 4.4;
    float r = 5;
    Sphere c1(Point3D(x, y, z), r);
    Sphere c2(Point3D(4, 5, 12.2), 6);

    // Act
    bool actual_result = (c1 == c2);

    // Assert
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}

