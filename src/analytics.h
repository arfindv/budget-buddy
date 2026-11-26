// Owner: Developer (Analytics) — п.4 категорії та %, п.8 період з рекурсією
#pragma once
#include "expense_array.h"
#include <string>

void showCategoryStats(const ExpenseArray& arr);                       // п.4
double sumForPeriodRecursive(const ExpenseArray& arr, int index,
                             const std::string& from, const std::string& to); // п.8
void showPeriodTotal(const ExpenseArray& arr);                          // п.8
