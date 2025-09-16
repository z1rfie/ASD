#define CIRCLE
#ifdef CIRCLE
#include "../lib_point/point.h"

class Circle {
	Point _center;
	float _radius;
public:
	Circle();
	Circle(Point, float);
	Circle(const Circle&);

	Point get_center();
	void set_center(Point c);

	float get_radius();
	void set_radius(float r);

	bool operator ==(const Circle&) const;
};

#endif // CIRCLE