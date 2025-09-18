#define TVECTOR
#ifdef TVECTOR

template<typename T>
class TriangleMatrix : public Matrix<T> {
public:
	TriangleMatrix() = default;
};

#endif // TVECTOR