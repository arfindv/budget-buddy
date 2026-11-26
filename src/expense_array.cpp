// Owner: Developer (Data Structures)
#include "expense_array.h"

ExpenseArray::ExpenseArray() : data_(nullptr), size_(0), capacity_(0) {}
ExpenseArray::~ExpenseArray() { delete[] data_; }

void ExpenseArray::grow() { /* TODO(Data Structures) */ }
void ExpenseArray::push(const Expense& e) { (void)e; /* TODO */ }
bool ExpenseArray::removeAt(int index) { (void)index; return false; /* TODO */ }
void ExpenseArray::insertAt(int index, const Expense& e) { (void)index; (void)e; /* TODO */ }
int ExpenseArray::size() const { return size_; }
Expense& ExpenseArray::operator[](int index) { return data_[index]; }
const Expense& ExpenseArray::operator[](int index) const { return data_[index]; }
