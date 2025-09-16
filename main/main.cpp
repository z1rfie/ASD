#include <iostream>

#define CIRCLE
#ifdef CIRCLE

#include <iomanip>
#include "../lib_circle/circle.h"

enum TypeTouch { ExternalTouch, Intersection, Coincidence, Inside, NotIntersect };

TypeTouch location_circles(Circle first_circle, Circle second_circle) {
	Point first_circle_center = first_circle.get_center();
	Point second_circle_center = second_circle.get_center();
	float distance = first_circle_center.distance_between_points(second_circle_center);

	float radius_first_circle = first_circle.get_radius();
	float radius_second_circle = second_circle.get_radius();

	if (distance > radius_first_circle + radius_second_circle) {
		return NotIntersect;
	}
	else if (distance < radius_first_circle - radius_second_circle) {
		return Inside;
	}
	else if (radius_first_circle - radius_second_circle < distance
		&& distance < radius_first_circle + radius_second_circle) {
		return Intersection;
	}
	else if (distance == radius_first_circle + radius_second_circle) {
		return ExternalTouch;
	}
	else if (radius_first_circle == radius_second_circle && distance == 0) {
		return Coincidence;
	}
}

int main() {
	Circle c1(Point(0, 0), 5);
	Circle c2(Point(0, 0), 3);
	std::cout << location_circles(c1, c2) << std::endl;

	Circle c4(Point(1, 2), 3);
	std::cout << location_circles(c1, c4) << std::endl;

	Circle c6(Point(6, 0), 1);
	std::cout << location_circles(c1, c6) << std::endl;

	Circle c8(Point(0, 0), 5);
	std::cout << location_circles(c1, c8) << std::endl;

	Circle c10(Point(7, 9), 3);
	std::cout << location_circles(c1, c10) << std::endl;

	return 0;
}

#endif  // CIRCLE

#ifdef MATRIX

#include "matrix.h"

int main() {
	setlocale(LC_ALL, "rus");

	size_t N1, M1;
	std::cout << "Введите количество строк и столбцов для первой матрицы через пробел: ";
	std::cin >> N1 >> M1;

	size_t N2, M2;
	std::cout << "Введите количество строк и столбцов для второй матрицы через пробел: ";
	std::cin >> N2 >> M2;

	Matrix<MathVector<size_t>> first_matrix(N1,M1);

	char operation;
	std::cout << "Выберите операцию (+, -, *): ";
	std::cin >> operation;

	switch (operation) {
	case '+': 
		std::cout << "to do +";
		break;
	case '-':
		std::cout << "to do -";
		break;
	case '*':
		std::cout << "to do *";
		break;
	}

	return 0;
}

#endif // MATRIX