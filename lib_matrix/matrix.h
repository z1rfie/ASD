#define MATRIX
#ifdef MATRIX
#include "../lib_math_vector/math_vector.h"

template<typename T>
class Matrix : public MathVector<MathVector<T>> {
	MathVector<MathVector<T>> _data;
public:
	Matrix() = default;
	Matrix(size_t M, size_t N) : MathVector<MathVector<T>>(M) {
		for (size_t i = 0; i < N; i++) {
			_data[i] = new MathVector<T>(M);
		}
	}
};

#endif // MATRIX