#ifndef LIB_UNSORTED_TABLE_M
#define LIB_UNSORTED_TABLE_M

#include "../lib_itable/itable.h"
#include "../lib_tvector/vector.h"

//template  <class TKey, class TValue>
//class UnsortedTableM : public ITable<TKey, TValue> {
//	TVector <std::pair<TKey, TValue>> _rows;
//public:
//	UnsortedTableM() : _rows() {}
//	~UnsortedTableM() {}
//
//	void insert(TKey key, TValue value) override { _rows.push_back_elem(std::make_pair(key, value)); }
//	void erase(TKey key) override { _rows.erase_elem(key); }
//	TValue& found(TKey key) override { return _rows.find_elem(key); }
//
//	bool is_empty() override { return _rows.is_empty(); }
//
//	template<typename U>
//	virtual friend std::ostream& operator<<(std::ostream&, const UnsortedTableM&);
//};

#endif  // LIB_UNSORTED_TABLE_M
