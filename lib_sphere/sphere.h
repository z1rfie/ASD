#include "../lib_point3D/point3D.h"
#pragma once

class Sphere {
	Point3D _center;
	float _radius;
public:
	Sphere();
	Sphere(Point3D, float);
	Sphere(const Sphere&);

	Point3D get_center();
	float get_radius();

	void set_center(Point3D center);
	void set_radius(float radius);

	bool operator ==(const Sphere&) const;
};