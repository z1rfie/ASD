#define TRIANGLE_MATRIX
#ifdef TRIANGLE_MATRIX
#include "../lib_matrix/matrix.h"

template<typename T>
class TriangleMatrix : public Matrix<T> {
public:
	TriangleMatrix();
	TriangleMatrix(size_t size);
	TriangleMatrix(const TriangleMatrix<T>& other);
	TriangleMatrix(const MathVector<MathVector<T>>& vec);

	TriangleMatrix<T> operator+(const TriangleMatrix<T>& other) const;
	TriangleMatrix<T>& operator+=(const TriangleMatrix<T>& other);

	TriangleMatrix<T> operator-(const TriangleMatrix<T>& other) const;
	TriangleMatrix<T>& operator-=(const TriangleMatrix<T>& other);

	TriangleMatrix<T> operator*(T val) const;
	TriangleMatrix<T>& operator*=(T val);

	TriangleMatrix<T> operator*(const TriangleMatrix<T>& matr) const;

	TriangleMatrix<T>& operator=(const TriangleMatrix<T>& matr);

	MathVector<T>& operator[](size_t index);
	const MathVector<T>& operator[](size_t index) const;

	bool operator==(const TriangleMatrix<T>& other) const;
	bool operator!=(const TriangleMatrix<T>& other) const;

    T& at(size_t i, size_t j);
	const T& at(size_t i, size_t j) const;

	void input_triangle(size_t size);
	void print_triangle() const;
};

template<typename T>
TriangleMatrix<T>::TriangleMatrix() : Matrix<T>(0) {}

template<typename T>
TriangleMatrix<T>::TriangleMatrix(size_t size) : Matrix<T>(size, size) {
	for (size_t i = 0; i < size; i++) {
		(*this)[i] = MathVector<T>(size - i, i);
	}
}

template<typename T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other) : Matrix<T>(other) {}

template<typename T>
TriangleMatrix<T>::TriangleMatrix(const MathVector<MathVector<T>>& vec) : Matrix<T>(vec.size(), vec.size()) {
	_N = vec.size();
	_M = _N; 

	for (size_t i = 0; i < _N; i++) {
		for (size_t j = i; j < _N; j++) {
			if (j < vec[i].size()) {
				(*this)[i][j] = vec[i][j];
			}
		}
	}
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) const {
	TriangleMatrix<T> result(this->_N);

	for (size_t i = 0; i < this->_N; i++) {
		for (size_t j = i; j < this->_N; j++) {
			result[i][j] = (*this)[i][j] + other[i][j];
		}
	}

	return result;
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator+=(const TriangleMatrix<T>& other) {
	for (size_t i = 0; i < this->_N; i++) {
		for (size_t j = i; j < this->_N; j++) {
			(*this)[i][j] += other[i][j];
		}
	}

	return *this;
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) const {
	TriangleMatrix<T> result(this->_N);

	for (size_t i = 0; i < this->_N; i++) {
		for (size_t j = i; j < this->_N; j++) {
			result[i][j] = (*this)[i][j] - other[i][j];
		}
	}

	return result;
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=(const TriangleMatrix<T>& other) {
	for (size_t i = 0; i < this->_N; i++) {
		for (size_t j = i; j < this->_N; j++) {
			(*this)[i][j] -= other[i][j];
		}
	}

	return *this;
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(T val) const {
	TriangleMatrix<T> result(this->_N);

	for (size_t i = 0; i < this->_N; i++) {
		for (size_t j = i; j < this->_N; j++) {
			result[i][j] = (*this)[i][j] * val;
		}
	}

	return result;
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(T val) {
	for (size_t i = 0; i < this->_N; i++) {
		for (size_t j = i; j < this->_N; j++) {
			(*this)[i][j] *= val;
		}
	}

	return *this;
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& matr) const {
	size_t n = this->_N;
	TriangleMatrix<T> result(n);

	for (size_t i = 0; i < n; i++) {
		for (size_t j = i; j < n; j++) {
			T sum = T(0);

			for (size_t k = i; k <= j; k++) {
				sum += (*this)[i][k] * matr[k][j];
			}

			result[i][j] = sum;
		}
	}

	return result;
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator=(const TriangleMatrix<T>& other) {
	if (this != &other) {
		_N = other._N;
		_M = other._M;
		MathVector<MathVector<T>>::operator=(other);
	}
	return *this;
}

template<typename T>
MathVector<T>& TriangleMatrix<T>::operator[](size_t index) {
	return MathVector<MathVector<T>>::operator[](index);
}

template<typename T>
const MathVector<T>& TriangleMatrix<T>::operator[](size_t index) const {
	return MathVector<MathVector<T>>::operator[](index);
}

template<typename T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& other) const {
	if (_N != other._N) {
		return false;
	}

	for (size_t i = 0; i < _N; i++) {
		for (size_t j = i; j < _N; j++) {
			if ((*this)[i][j] != other[i][j]) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>& other) const {
	return !(*this == other);
}

template<typename T>
T& TriangleMatrix<T>::at(size_t i, size_t j) {
	if (i >= this->_N || j >= this->_N) {  
		throw std::out_of_range("TriangleMatrix indices out of range");
	}
	return (*this)[i][j];
}

template<typename T>
const T& TriangleMatrix<T>::at(size_t i, size_t j) const {
	if (i >= this->_N || j >= this->_N) {
		throw std::out_of_range("TriangleMatrix indices out of range");
	}
	return (*this)[i][j];
}

template<typename T>
void TriangleMatrix<T>::input_triangle(size_t size) {
	this->resize(size, size);

	for (size_t i = 0; i < size; i++) {
		(*this)[i] = MathVector<T>(size - i, i);

		std::cout << "Row " << (i + 1) << ": ";
		for (size_t j = i; j < size; j++) {
			std::cin >> (*this)[i][j];
		}
	}
}

template<typename T>
void TriangleMatrix<T>::print_triangle() const {
	size_t n = this->get_n();
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			if (j >= i) {
				std::cout << (*this)[i][j] << " ";
			}
			else {
				std::cout << "0 "; 
			}
		}
		std::cout << std::endl;
	}
}

#endif // TRIANGLE_MATRIX