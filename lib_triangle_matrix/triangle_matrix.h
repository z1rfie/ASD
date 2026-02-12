//#define TRIANGLE_MATRIX
//#ifdef TRIANGLE_MATRIX

#pragma once

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

	MathVector<T> operator*(const MathVector<T>& vec) const;

	TriangleMatrix<T>& operator=(const TriangleMatrix<T>& matr);
	TriangleMatrix<T>& operator=(const MathVector<T>& vector);

	MathVector<T>& operator[](size_t index);
	const MathVector<T>& operator[](size_t index) const;

	bool operator==(const TriangleMatrix<T>& other) const;
	bool operator!=(const TriangleMatrix<T>& other) const;

    T& at(size_t i, size_t j);
	const T& at(size_t i, size_t j) const;

	template<typename U>
	friend std::istream& operator>>(std::istream& is, TriangleMatrix<U>& matrix);

	template<typename U>
	friend std::ostream& operator<<(std::ostream& os, const TriangleMatrix<U>& matrix);
};

template<typename T>
TriangleMatrix<T>::TriangleMatrix() : Matrix<T>(0) {}

template<typename T>
TriangleMatrix<T>::TriangleMatrix(size_t size) : Matrix<T>(size, size) {
	for (size_t i = 0; i < size; i++) {
		_data[i] = MathVector<T>(size - i, i);
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
				_data[i][j] = vec[i][j];
			}
		}
	}
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) const { 
	TriangleMatrix<T> result(_N);

	for (size_t i = 0; i < _N; i++) {
		for (size_t j = i; j < _N; j++) {
			result[i][j] = _data[i][j] + other[i][j];
		}
	}

	return result;
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator+=(const TriangleMatrix<T>& other) {
	for (size_t i = 0; i < _N; i++) {
		for (size_t j = i; j < _N; j++) {
			_data[i][j] += other[i][j];
		}
	}

	return *this;
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) const {
	TriangleMatrix<T> result(_N);

	for (size_t i = 0; i < _N; i++) {
		for (size_t j = i; j < _N; j++) {
			result[i][j] = _data[i][j] - other[i][j];
		}
	}

	return result;
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=(const TriangleMatrix<T>& other) {
	for (size_t i = 0; i < _N; i++) {
		for (size_t j = i; j < _N; j++) {
			_data[i][j] -= other[i][j];
		}
	}

	return *this;
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(T val) const {
	TriangleMatrix<T> result(_N);

	for (size_t i = 0; i < _N; i++) {
		for (size_t j = i; j < _N; j++) {
			result[i][j] = _data[i][j] * val;
		}
	}

	return result;
}

template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(T val) {
	for (size_t i = 0; i < _N; i++) {
		for (size_t j = i; j < _N; j++) {
			_data[i][j] *= val;
		}
	}

	return *this;
}

template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& matr) const {
	TriangleMatrix<T> result(_N);

	for (size_t i = 0; i < _N; i++) {
		for (size_t j = i; j < _N; j++) {
			T sum = T(0);

			for (size_t k = i; k <= j; k++) {
				sum += _data[i][k] * matr[k][j];
			}

			result[i][j] = sum;
		}
	}

	return result;
}

template<typename T>
MathVector<T> TriangleMatrix<T>::operator*(const MathVector<T>& vec) const {
	if (_M != vec.size()) {
		throw std::invalid_argument("Matrix columns must match vector size");
	}

	MathVector<T> result(_N); 

	for (size_t i = 0; i < _N; i++) {
		result[i] = T(0); 

		for (size_t j = i; j < _M; j++) {
			result[i] += _data[i][j] * vec[j];
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
			if (_data[i][j] != other[i][j]) {
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
	if (i >= _N || j >= _N) {  
		throw std::out_of_range("TriangleMatrix indices out of range");
	}
	return _data[i][j];
}

template<typename T>
const T& TriangleMatrix<T>::at(size_t i, size_t j) const {
	if (i >= _N || j >= _N) {
		throw std::out_of_range("TriangleMatrix indices out of range");
	}
	return _data[i][j];
}

template<typename T>
std::istream& operator>>(std::istream& is, TriangleMatrix<T>& matrix) {
	size_t size = matrix.get_n();

	for (size_t i = 0; i < size; i++) {
		matrix[i] = MathVector<T>(size - i, i);

		std::cout << "Row " << (i + 1) << ": ";
		for (size_t j = i; j < size; j++) {
			is >> matrix[i][j];
		}
	}
	return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const TriangleMatrix<T>& matrix) {
	size_t size = matrix.get_n();

	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			if (j >= i) {
				os << matrix[i][j] << " ";
			}
			else {
				os << "0 ";
			}
		}
		os << std::endl;
	}
	return os;
}

//#endif // TRIANGLE_MATRIX