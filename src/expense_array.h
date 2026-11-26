// Owner: Developer (Data Structures) — динамічний масив витрат
#pragma once
#include "expense.h"

class ExpenseArray {
public:
    ExpenseArray();
    ~ExpenseArray();
    ExpenseArray(const ExpenseArray&) = delete;
    ExpenseArray& operator=(const ExpenseArray&) = delete;

    void push(const Expense& e);
    bool removeAt(int index);
    void insertAt(int index, const Expense& e);
    int size() const;
    Expense& operator[](int index);
    const Expense& operator[](int index) const;

private:
    Expense* data_;
    int size_;
    int capacity_;
    void grow();
};
