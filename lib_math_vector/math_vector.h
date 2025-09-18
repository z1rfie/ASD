#define MATH_VECTOR
#ifdef MATH_VECTOR
#include "../lib_tvector/vector.h"

template<typename T> 
class MathVector : public TVector<T> {
	size_t _start_index;
public:
	MathVector() = default; 
	MathVector(size_t size);

	void input_vector();
};

template<typename T>
MathVector<T>::MathVector(size_t size) {

}

template<typename T>
void MathVector<T>::input_vector() {
	std::cout << std::endl << "to do input vector" << std::endl;
}

#endif // MATH_VECTOR