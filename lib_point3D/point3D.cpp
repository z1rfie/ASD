#include "point3D.h"
#include <corecrt_math.h>

Point3D::Point3D() : Point(0, 0), _z(0) {}
Point3D::Point3D(float x, float y, float z) : Point(x, y), _z(z) {}
Point3D::Point3D(const Point3D& other) : Point(other), _z(other._z) {}

float Point3D::get_z() { return _z; }
void Point3D::set_z(float z) { _z = z; }

float Point3D::distance_between_points(const Point3D& other) {
	float distance = ((other._x - _x) * (other._x - _x) +
		(other._y - _y) * (other._y - _y) + (other._z - _z) * (other._z - _z));
	return sqrt(distance);
}