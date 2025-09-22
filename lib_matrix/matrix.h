#define MATRIX
#ifdef MATRIX
#include "../lib_math_vector/math_vector.h"
#include <iostream>

template<typename T>
class Matrix : public MathVector<MathVector<T>> {
	size_t _N;
	size_t _M;
	//size_t _size;
public:
	Matrix() = default;
	Matrix(size_t N, size_t M);
	//Matrix(size_t size) : _size(size) {}

	Matrix<T> operator+(const Matrix<T> matr) const;
	Matrix<T> operator-(const Matrix<T> matr) const;
	Matrix<T> operator*(T val) const;
	MathVector<T> operator*(const MathVector<T> vec) const;
	Matrix<T> operator*(const Matrix<T> matr) const;
	Matrix<T>& operator=(const MathVector<T>& vector); 
	MathVector<T>& operator[](size_t index);

	size_t get_n();
	size_t get_m();

	void transposition_matrix();

	void input_matrix();
	void print_matrix() const;
private:
	bool is_valid_matrix() const;
};

template<typename T>
Matrix<T>::Matrix(size_t N, size_t M) : _N(N), _M(M) {}
//Matrix(size_t size) : _size(size) {}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> matr) const  {
	std::cout << std::endl << "to do +" << std::endl;
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> matr) const {
	std::cout << std::endl << "to do -" << std::endl;
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T val) const {
	std::cout << std::endl << "to do * scalar" << std::endl;
	return *this;
}

template<typename T>
MathVector<T> Matrix<T>::operator*(const MathVector<T> vec) const {
	std::cout << std::endl << "to do * vec" << std::endl;
	return MathVector<T>(_N);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> matr) const {
	std::cout << std::endl << "to do *" << std::endl;
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const MathVector<T>& vector) {
	std::cout << std::endl << "to do = " << std::endl;
	return *this;
}

template<typename T>
size_t Matrix<T>::get_n() { return _N; }

template<typename T>
size_t Matrix<T>::get_m() { return _M; }

template<typename T>
void Matrix<T>::transposition_matrix() {
	std::cout << std::endl << "to do transposition" << std::endl;
}

template<typename T>
void Matrix<T>::input_matrix() {
	std::cout << std::endl << "to do input" << std::endl;
}

template<typename T>
void Matrix<T>::print_matrix() const {
	std::cout << std::endl << "to do print" << std::endl;
}

#endif // MATRIX