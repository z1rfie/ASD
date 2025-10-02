#define MATH_VECTOR
#ifdef MATH_VECTOR
#include "../lib_tvector/vector.h"

template<typename T> 
class MathVector : public TVector<T> {
protected:
	size_t _start_index;
public:
	MathVector(); 
	MathVector(size_t N);
	MathVector(size_t N, size_t start_index);
	MathVector(const MathVector<T>&);

	MathVector<T> operator+(const MathVector<T>& other) const;
	MathVector<T>& operator+=(const MathVector<T>& other);

	MathVector<T> operator-(const MathVector<T>& other) const;
	MathVector<T>& operator-=(const MathVector<T>& other);

	MathVector<T> operator*(T val) const;
	MathVector<T>& operator*=(T val);

	T operator*(MathVector<T> vec) const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	// добавить at и проверку вектора? и что с операторами вывода делать

	MathVector<T>& operator=(const MathVector<T>& other);

	size_t get_size() const { return TVector<T>::size(); }

	template<typename U>
	friend std::ostream& operator<<(std::ostream& os, const MathVector<T>& vec);
	template<typename U>
	friend std::istream& operator>>(std::istream& is, MathVector<T>& vec);

	void input_vector();
	void print_vector() const;
};

template<typename T>
MathVector<T>::MathVector() : TVector<T>(), _start_index(0) {}

template<typename T>
MathVector<T>::MathVector(size_t size, size_t start_index) : TVector<T>(size), _start_index(start_index) {}

template<typename T>
MathVector<T>::MathVector(size_t size) : TVector<T>(size), _start_index(0) {}

template<typename T>
MathVector<T>::MathVector(const MathVector<T>& other) : TVector<T>(other), _start_index(other._start_index) {}

template<typename T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other) const {
	MathVector<T> result(get_size(), _start_index);

	for (size_t i = 0; i < get_size(); i++) {
		result[i] = (*this)[i] + other[i];
	}

	return result;
}

template<typename T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& other) {
	for (size_t i = 0; i < get_size(); i++) {
		(*this)[i] += other[i];
	}

	return *this;
}

template<typename T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other) const {
	MathVector<T> result(get_size(), _start_index);

	for (size_t i = 0; i < get_size(); i++) {
		result[i] = (*this)[i] - other[i];
	}

	return result;
}

template<typename T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& other) {
	for (size_t i = 0; i < get_size(); i++) {
		(*this)[i] -= other[i];
	}

	return *this;
}

template<typename T>
MathVector<T> MathVector<T>::operator*(T val) const {
	MathVector<T> result(get_size(), _start_index);

	for (size_t i = 0; i < get_size(); i++) {
		result[i] = (*this)[i] * val;
	}

	return result;
}

template<typename T>
MathVector<T>& MathVector<T>::operator*=(T val) {
	for (size_t i = 0; i < get_size(); i++) {
		(*this)[i] *= val;
	}

	return *this;
}

template<typename T>
T MathVector<T>::operator*(MathVector<T> vec) const {
	T result = T();

	for (size_t i = 0; i < get_size(); i++) {
		result += ((*this)[i] * vec[i]);
	}

	return result;
}

template<typename T>
MathVector<T>& MathVector<T>::operator=(const MathVector<T>& other) {
	if (this != &other) { 
		_start_index = other._start_index;

		TVector<T>::operator=(other);
	}
	return *this;
}

template<typename T>
T& MathVector<T>::operator[](size_t index) {
	//if (index - _start_index < 0) return T();
	return _data[index - _start_index];
}

template<typename T>
const T& MathVector<T>::operator[](size_t index) const {
	//if (index - _start_index < 0) return T();
	return _data[index - _start_index];
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const MathVector<T>& vec) {
	os << '[';
	for (size_t i = 0; i < vec.get_size(); ++i) {
		os << vec[i];
		if (i + 1 < vec.get_size())
			os << ", ";
	}
	return os << ']';
}

template<typename T>
std::istream& operator>>(std::istream& is, MathVector<T>& vec) {
	for (size_t i = 0; i < vec.get_size(); ++i) {
		is >> vec[i];
	}
	return is;
}


template<typename T>
void MathVector<T>::input_vector() {
	for (size_t i = 0; i < get_size(); i++) {
		std::cin >> (*this)[i];
	}
}

template<typename T>
void MathVector<T>::print_vector() const {
	for (size_t i = 0; i < get_size(); i++) {
		std::cout << (*this)[i] << ' '; 
	}
	std::cout << std::endl;
}
#endif // MATH_VECTOR