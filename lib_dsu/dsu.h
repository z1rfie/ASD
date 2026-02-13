#define LIB_DSU
#ifdef LIB_DSU

#include <stdexcept>

class DSU {
	int* _parent;
	int* _rank;
	size_t _size;
public:
	DSU(size_t size); //1 test
	DSU(const DSU&); //1 test
	~DSU();

	const int* parent() const;
	int* parent();
	const int* rank() const;
	const size_t size() const;

	void func_union(int x, int y); //5 tests
	int find(int x); //2 tests
	int find_rec(int x); //2 tests
};

#endif // LIB_DSU
