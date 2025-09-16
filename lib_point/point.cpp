#include "point.h"
#include <cmath>

Point::Point() : _x(0), _y(0) {}
Point::Point(float x, float y) : _x(x), _y(y) {}
Point::Point(const Point& other) : _x(other._x),
_y(other._y) {
}
float Point::get_x() { return _x; }
float Point::get_y() { return _y; }

void Point::set_x(float x) { _x = x; }
void Point::set_y(float y) { _y = y; }

bool Point::operator ==(const Point& other) const {
	return (_x == other._x) && (_y == other._y);
}

float Point::distance_between_points(const Point& other) {
	float distance = ((other._x - _x) * (other._x - _x) +
		(other._y - _y) * (other._y - _y));
	return sqrt(distance);
}