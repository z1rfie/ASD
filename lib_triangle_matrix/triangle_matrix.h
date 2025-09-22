#define TRIANGLE_MATRIX
#ifdef TRIANGLE_MATRIX

template<typename T>
class TriangleMatrix : public Matrix<T> {
	bool _is_upper;
public:
	TriangleMatrix() = default;
	TriangleMatrix(size_t size, bool is_upper);
	TriangleMatrix(const TriangleMatrix<T>& other);

	TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other);
    TriangleMatrix<T> operator+(const TriangleMatrix<T>& other) const;
    TriangleMatrix<T> operator-(const TriangleMatrix<T>& other) const;
    TriangleMatrix<T> operator*(T scalar) const;
    TriangleMatrix<T> operator*(const TriangleMatrix<T>& other) const;

	bool is_upper() const;

	void input_triangle();
	void print_triangle() const;
private:
	bool is_valid_triangle() const;
};

#endif // TRIANGLE_MATRIX