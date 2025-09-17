#define MATRIX
#ifdef MATRIX
#include "../lib_math_vector/math_vector.h"
#include <iostream>

template<typename T>
class Matrix : public MathVector<MathVector<T>> {
	size_t _N;
	size_t _M;
public:
	Matrix() = default;
	Matrix(size_t N, size_t M) : _N(N), _M(M) {}

	Matrix<T> operator+(Matrix<T> matr) {
		std::cout << std::endl << "to do +" << std::endl;
		return *this;
	}
	Matrix<T> operator-(Matrix<T> matr) {
		std::cout << std::endl << "to do -" << std::endl;
		return *this;
	}
	Matrix<T> operator*(Matrix<T> matr) {
		std::cout << std::endl << "to do *" << std::endl;
		return *this;
	}

	void input_matrix() {
		std::cout << std::endl << "to do input" << std::endl;
	}
	void print_matrix() {
		std::cout << std::endl << "to do print" << std::endl;
	}
};

#endif // MATRIX