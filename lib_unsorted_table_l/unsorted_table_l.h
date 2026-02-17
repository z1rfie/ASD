#ifndef LIB_UNSORTED_TABLE_L
#define LIB_UNSORTED_TABLE_L

#include "../lib_table/table.h"
#include "../lib_list/list.h"

template  <class TKey, class TValue>
class UnsortedTableL : public Table<TKey, TValue> {
	List<std::pair<TKey, TValue>> _rows;
public:
	UnsortedTableL() = default;
	~UnsortedTableL() {}

	void insert(const TKey&, const TValue& value) override;
	void erase(const TKey&) override;
	TValue& found(const TKey&) override;

	bool is_empty() const noexcept override;

	void print(std::ostream& os) const override;
};

template  <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	for (auto it = _rows.begin(); it != _rows.end(); it++) {
		if ((*it).first == key) {
			throw std::logic_error("The key is already occupied");
		}
	}
	_rows.push_back(std::make_pair(key, value));
}

template  <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::erase(const TKey& key) {
	for (auto it = _rows.begin(); it != _rows.end(); it++) {
		if ((*it).first == key) {
			_rows.erase(it.get_node());
			return;
		}
	}
	throw std::logic_error("The key was not found");
}

template <class TKey, class TValue>
TValue& UnsortedTableL<TKey, TValue>::found(const TKey& key)  {
	for (auto it = _rows.begin(); it != _rows.end(); it++) {
		if ((*it).first == key) {
			return (*it).second;  
		}
	}
	throw std::logic_error("The key was not found");
}

template  <class TKey, class TValue>
bool UnsortedTableL<TKey, TValue>::is_empty() const noexcept {
	return _rows.is_empty();
}

template  <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::print(std::ostream& os) const {
	for (auto it = _rows.begin(); it != _rows.end(); it++) {
		os << "| " << (*it).first << " | " << (*it).second << " |" << std::endl;
	}
}

#endif  // LIB_UNSORTED_TABLE_L
