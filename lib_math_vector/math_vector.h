#define MATH_VECTOR
#ifdef MATH_VECTOR
#include "../lib_tvector/vector.h"

template<typename T> 
class MathVector : public TVector<T> {
public:
	MathVector() = default; 
};

#endif // MATH_VECTOR