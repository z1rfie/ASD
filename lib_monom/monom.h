#include <stdexcept>
#include <cmath>
#include <iostream>

#define VARS_COUNT 3

class Monom {
	double _coefficient;
	int _powers[VARS_COUNT];
public:
	Monom(double coefficient = 0.0) : _coefficient(coefficient) {
		for (int i = 0; i < VARS_COUNT; i++) {
			_powers[i] = 0;
		}
	}

	Monom(double coefficient, int powers[VARS_COUNT]) : _coefficient(coefficient) {
		for (int i = 0; i < VARS_COUNT; i++) {
			_powers[i] = powers[i];
		}
	}

	Monom(const Monom& other) : _coefficient(other._coefficient) {
		for (int i = 0; i < VARS_COUNT; i++) {
			_powers[i] = other._powers[i];
		}
	}

	bool operator==(const Monom& other) const {
		for (int i = 0; i < VARS_COUNT; i++) {
			if (_powers[i] != other._powers[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Monom& other) const {
		return !(*this == other);
	}

	bool operator>(const Monom& other) const {
		for (int i = 0; i < VARS_COUNT; i++) {
			if (_powers[i] > other._powers[i]) return true;
			if (_powers[i] < other._powers[i]) return false;
		}
		return false;
	}

	bool operator<(const Monom& other) const {
		return other > *this; 
	}

	Monom& operator=(const Monom& other) {
		if (this != &other) {
			_coefficient = other._coefficient;
			for (int i = 0; i < VARS_COUNT; i++) {
				_powers[i] = other._powers[i];
			}
		}
		return *this;
	}

	Monom operator+(const Monom& other) const {
		if (*this != other) {
			throw std::invalid_argument("Cannot add monomials with different powers");
		}

		Monom res(*this);
		res._coefficient += other._coefficient;
		return res;
	}

	Monom& operator+=(const Monom& other) {
		if (*this != other) {
			throw std::invalid_argument("Cannot add monomials with different powers");
		}
		
		_coefficient += other._coefficient;
		return *this;
	}

	Monom operator-(const Monom& other) const {
		if (*this != other) {
			throw std::invalid_argument("Cannot sub monomials with different powers");
		}

		Monom res(*this);
		res._coefficient -= other._coefficient;
		return res;
	}

	Monom operator-() const {
		Monom res(*this);
		res._coefficient = -res._coefficient;
		return res;
	}

	Monom& operator-=(const Monom& other) {
		if (*this != other) {
			throw std::invalid_argument("Cannot sub monomials with different powers");
		}

		_coefficient -= other._coefficient;
		return *this;
	}

	Monom operator*(const Monom& other) const {
		Monom res(*this);
		res._coefficient *= other._coefficient;
		for (int i = 0; i < VARS_COUNT; i++) {
			res._powers[i] += other._powers[i];
		}
		return res;
	}

	Monom operator*(double scalar) const {
		Monom res(*this);
		res._coefficient *= scalar;
		return res;
	}

	Monom& operator*=(const Monom& other) {
		_coefficient *= other._coefficient;
		for (int i = 0; i < VARS_COUNT; i++) {
			_powers[i] += other._powers[i];
		}
		return *this;
	}

	Monom operator/(const Monom& other) const {
		if (std::abs(other._coefficient) < 1e-9) {
			throw std::invalid_argument("Division by zero");
		}

		Monom res(*this);
		res._coefficient /= other._coefficient;
		for (int i = 0; i < VARS_COUNT; i++) {
			if (_powers[i] < other._powers[i]) {
				throw std::invalid_argument("Division would result in negative power");
			}
			res._powers[i] -= other._powers[i];
		}

		return res;
	}

	Monom operator/(double scalar) const {
		if (std::abs(scalar) < 1e-9)
			throw std::invalid_argument("Division by zero");
		Monom res(*this);
		res._coefficient /= scalar;
		return res;
	}

	Monom& operator/=(const Monom& other) {
		if (std::abs(other._coefficient) < 1e-9) {
			throw std::invalid_argument("Division by zero");
		}

		_coefficient /= other._coefficient;
		for (int i = 0; i < VARS_COUNT; i++) {
			if (_powers[i] < other._powers[i]) {
				throw std::invalid_argument("Division would result in negative power");
			}
			_powers[i] -= other._powers[i];
		}

		return *this;
	}

	double calculate_value_point_monom(double x, double y, double z) const {
		return _coefficient * std::pow(x, _powers[0]) * std::pow(y, _powers[1]) * std::pow(z, _powers[2]);
	}

	friend std::ostream& operator<<(std::ostream& os, const Monom& m) {
		os << m._coefficient;
		char vars[] = { 'x', 'y', 'z' };
		for (int i = 0; i < VARS_COUNT; i++) {
			if (m._powers[i] != 0) {
				os << vars[i];
				if (m._powers[i] != 1) os << "^" << m._powers[i];
			}
		}
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Monom& m) {
		is >> m._coefficient;
		for (int i = 0; i < VARS_COUNT; i++) {
			is >> m._powers[i];
		}
		return is;
	}
};