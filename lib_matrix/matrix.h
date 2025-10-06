#define MATRIX
#ifdef MATRIX
#include "../lib_math_vector/math_vector.h"
#include <iostream>

template<typename T>
class Matrix : public MathVector<MathVector<T>> {
protected:
	size_t _N;
	size_t _M;
public:
	Matrix();
	Matrix(size_t N, size_t M);
	Matrix(const Matrix<T>& other);
	Matrix(const MathVector<MathVector<T>>& vec);

	Matrix<T> operator+(const Matrix<T>& other) const;
	Matrix<T>& operator+=(const Matrix<T>& other);

	Matrix<T> operator-(const Matrix<T>& other) const;
	Matrix<T>& operator-=(const Matrix<T>& other);

	Matrix<T> operator*(T val) const;
	Matrix<T>& operator*=(T val);

	MathVector<T> operator*(const MathVector<T>& vec) const;

	Matrix<T> operator*(const Matrix<T>& matr) const;

	Matrix<T>& operator=(const MathVector<T>& vector); 
	Matrix<T>& operator=(const Matrix<T>& matr);

	MathVector<T>& operator[](size_t index);
	const MathVector<T>& operator[](size_t index) const;

	T& at(size_t i, size_t j);
	const T& at(size_t i, size_t j) const;

	bool operator==(const Matrix<T>& other) const;
	bool operator!=(const Matrix<T>& other) const;

	size_t get_n() const;
	size_t get_m() const;

	void transposition_matrix();

	void input_matrix(size_t N, size_t M);
	void print_matrix() const;
};

template<typename T>
Matrix<T>::Matrix() : MathVector<MathVector<T>>(0), _N(0), _M(0) {}

template<typename T>
Matrix<T>::Matrix(size_t N, size_t M) : MathVector<MathVector<T>>(N), _N(N), _M(M) { 
	for (size_t i = 0; i < N; i++) {
		(*this)[i] = MathVector<T>(_M);
	}
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : MathVector<MathVector<T>>(other), _N(other._N), _M(other._M) {}

template <typename T>
Matrix <T>::Matrix(const MathVector<MathVector<T>>& vec) : MathVector<MathVector<T>>(vec), _N(vec.size()), _M(_N > 0 ? vec[0].size() : 0) {}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
	return this->MathVector<MathVector<T>>::operator+(other);
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
	this->MathVector<MathVector<T>>::operator+=(other);
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
	return this->MathVector<MathVector<T>>::operator-(other);
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
	this->MathVector<MathVector<T>>::operator-=(other);
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T val) const {
	Matrix<T> result(_N, _M);

	for (size_t i = 0; i < _N; i++) {
		result[i] = (*this)[i] * val;  
	}

	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(T val) {
	for (size_t i = 0; i < _N; i++) {
		(*this)[i] *= val; 
	}

	return *this;
}

template<typename T>
MathVector<T> Matrix<T>::operator*(const MathVector<T>& vec) const {
	MathVector<T> result(_N);

	for (size_t i = 0; i < _N; i++) {
		for (size_t j = 0; j < _M; j++) {
			result[i] = (*this)[i] * vec;
		}
	}

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matr) const {
	Matrix<T> result(_N, matr._M);
	Matrix<T> transposed_matr = matr;
	transposed_matr.transposition_matrix();

	for (size_t i = 0; i < _N; i++) {
		for (size_t j = 0; j < matr._M; j++) {
			result[i][j] = (*this)[i] * transposed_matr[j];
		}
	}

	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
	if (this != &other) {
		_N = other._N;
		_M = other._M;
		MathVector<MathVector<T>>::operator=(other);
	}
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const MathVector<T>& vec) {
	_N = vec.size();
	_M = 1;

	MathVector<MathVector<T>>::resize(_N);
	for (size_t i = 0; i < _N; i++) {
		(*this)[i] = MathVector<T>(1); 
		(*this)[i][0] = vec[i];         
	}

	return *this;
}

template<typename T>
MathVector<T>& Matrix<T>::operator[](size_t index) {
	return MathVector<MathVector<T>>::operator[](index);
}

template<typename T>
const MathVector<T>& Matrix<T>::operator[](size_t index) const {
	return MathVector<MathVector<T>>::operator[](index);
}

template<typename T>
T& Matrix<T>::at(size_t i, size_t j) {
	if (i >= _N || j >= _M) {
		throw std::out_of_range("Matrix indices out of range");
	}
	return (*this)[i][j];
}

template<typename T>
const T& Matrix<T>::at(size_t i, size_t j) const {
	if (i >= _N || j >= _M) {
		throw std::out_of_range("Matrix indices out of range");
	}
	return (*this)[i][j];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
	if (_N != other._N || _M != other._M) {
		return false;
	}

	return MathVector<MathVector<T>>::operator==(other);
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const {
	return !(*this == other);
}

template<typename T>
size_t Matrix<T>::get_n() const { return _N; }

template<typename T>
size_t Matrix<T>::get_m() const { return _M; }

template<typename T>
void Matrix<T>::transposition_matrix() {
	Matrix<T> transposed(_M, _N);

	for (size_t i = 0; i < _N; i++) {
		for (size_t j = 0; j < _M; j++) {
			transposed[j][i] = (*this)[i][j];
		}
	}

	size_t temp = _N;
	_N = _M;
	_M = temp;

	*this = transposed;
}

template<typename T>
void Matrix<T>::input_matrix(size_t N, size_t M) {
	this->resize(N, M);
	for (size_t i = 0; i < N; i++) {
		std::cout << "Row " << i + 1 << ": ";
		MathVector<T> row_vector(M);
		row_vector.input_vector();

		for (size_t j = 0; j < M; j++) {
			(*this)[i][j] = row_vector[j];  
		}
	}
}

template<typename T>
void Matrix<T>::print_matrix() const {
	for (size_t i = 0; i < _N; i++) {
		for (size_t j = 0; j < _M; j++) {
			std::cout << (*this)[i][j] << " ";  
		}
		std::cout << std::endl;
	}
}
#endif // MATRIX