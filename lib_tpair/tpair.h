#ifndef LIB_TPAIR
#define LIB_TPAIR

template  <class TKey, class TValue>
struct TPair {
	TKey key;
	TValue value;

	TKey get_key() const { return key; }
	TValue get_value() const { return value; }
};

#endif  // LIB_TPAIR