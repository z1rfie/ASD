#pragma once
#include "../lib_point/point.h"

class Point3D : public Point {
	float _z;
public:
	Point3D();
	Point3D(float, float, float);
	Point3D(const Point3D& other);

	float get_z();
	void set_z(float z);

	float distance_between_points(const Point3D& other);
};