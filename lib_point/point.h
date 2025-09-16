#pragma once

class Point {
protected:
	float _x;
	float _y;
public:
	Point();
	Point(float, float);
	Point(const Point& other);

	float get_x();
	float get_y();

	void set_x(float x);
	void set_y(float y);

	bool operator ==(const Point&) const;

	virtual float distance_between_points(const Point& other);
};