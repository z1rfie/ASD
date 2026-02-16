#ifndef LIB_ITABLE
#define LIB_ITABLE

#include <iostream>

template  <class TKey, class TValue>
class ITable {
public:
	virtual ~ITable() = default;
	virtual void insert(const TKey&, const TValue&) = 0;
	virtual void erase(const TKey&) = 0;
	virtual TValue& found(const TKey&) = 0;
	virtual bool is_empty() const noexcept = 0;
};

#endif  // LIB_ITABLE