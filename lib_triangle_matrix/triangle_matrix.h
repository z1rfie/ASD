#define TRIANGLE_MATRIX
#ifdef TRIANGLE_MATRIX

template<typename T>
class TriangleMatrix : public Matrix<T> {
	size_t _size;
public:
	TriangleMatrix() = default;
	TriangleMatrix(size_t size);
	TriangleMatrix(const TriangleMatrix<T>& other);

	TriangleMatrix<T>& operator=(const MathVector<T>& other);
	TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other);

    TriangleMatrix<T> operator+(const TriangleMatrix<T>& other) const;
    TriangleMatrix<T> operator-(const TriangleMatrix<T>& other) const;

    TriangleMatrix<T> operator*(T scalar) const;
	MathVector<T> operator*(const MathVector<T> vec) const;
    TriangleMatrix<T> operator*(const TriangleMatrix<T>& other) const;

	size_t get_size() const;

	void input_triangle();
	void print_triangle() const;
private:
	bool is_valid_triangle() const;
};

template<typename T>
TriangleMatrix<T>::TriangleMatrix(size_t size) : _size(size) {
}
template<typename T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other)  {
}
template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator=(const MathVector<T>& other) {
	return *this;
}
template<typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator=(const TriangleMatrix<T>& other) {
	return *this;
}
template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) const {
	return *this;
}
template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) const {
	return *this;
}
template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(T scalar) const {
	return *this;
}
template<typename T>
MathVector<T> TriangleMatrix<T>::operator*(const MathVector<T> vec) const {
	return MathVector<T>(_size);
}
template<typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& other) const {
	return *this;
}

template<typename T>
size_t TriangleMatrix<T>::get_size() const { return _size;  }

template<typename T>
void TriangleMatrix<T>::input_triangle() {

}
template<typename T>
void TriangleMatrix<T>::print_triangle() const {

}

#endif // TRIANGLE_MATRIX