#include <stdexcept>
#include "sphere.h"

Sphere::Sphere() : _center(Point3D(0, 0, 0)), _radius(1) {}
Sphere::Sphere(Point3D center, float radius) : _center(center), _radius(radius) {
	if (radius < 1) {
		throw std::invalid_argument("The radius cannot be less than one");
	}
}
Sphere::Sphere(const Sphere& other) : _center(other._center), _radius(other._radius) {}

Point3D Sphere::get_center() { return _center; }
float Sphere::get_radius() { return _radius; }

void Sphere::set_center(Point3D center) { _center = center; }
void Sphere::set_radius(float radius) { _radius = radius; }

bool Sphere::operator ==(const Sphere& other) const {
	return (_center == other._center) && (_radius == other._radius);
}