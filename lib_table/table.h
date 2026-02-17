#ifndef LIB_TABLE
#define LIB_TABLE

#include <iostream>
#include "../lib_itable/itable.h"

template  <class TKey, class TValue>
class Table : public ITable<TKey, TValue> {
public:
    virtual void print(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Table<TKey, TValue>& table) {
        table.print(os);
        return os;
    }
};

#endif  // LIB_TABLE