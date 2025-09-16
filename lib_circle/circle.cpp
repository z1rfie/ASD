#include <stdexcept>
#include "circle.h"

Circle::Circle() : _center(Point(0,0)), _radius(1) {}
Circle::Circle(Point p, float r) : _center(p), _radius(r) {
	if (r < 1) {
		throw std::invalid_argument("The radius cannot be less than one");
	}
}
Circle::Circle(const Circle& other) : _center(other._center), _radius(other._radius) {}

float Circle::get_radius() { return _radius; }
void Circle::set_radius(float r) { _radius = r; }

Point Circle::get_center() { return _center; }
void Circle::set_center(Point c) { _center = c; }

bool Circle::operator ==(const Circle& other) const {
	return (_center == other._center) && (_radius == other._radius);
}