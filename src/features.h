// Спільні оголошення функцій меню. Кожен реалізує свою у своєму .cpp
#pragma once
#include "expense_array.h"
#include "action_stack.h"

void addManual(ExpenseArray& arr, ActionStack& history);   // п.1  Core        add_manual.cpp
void addFromLine(ExpenseArray& arr, ActionStack& history); // п.2  Parser      parser.cpp / main
void showTable(const ExpenseArray& arr);                   // п.3  Presenter   display.cpp
void searchExpenses(const ExpenseArray& arr);              // п.5  Docs/UX     search.cpp
void showLargest(const ExpenseArray& arr);                 // п.6  Presenter   display.cpp
void checkBudget(const ExpenseArray& arr);                 // п.7  QA Lead     budget.cpp
void deleteExpense(ExpenseArray& arr, ActionStack& history); // п.9 QA Lead    delete.cpp
void undoLast(ExpenseArray& arr, ActionStack& history);    // п.10 Data Str.   undo.cpp
