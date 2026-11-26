// Owner: Developer (Parser) — ручний розбір через find/substr
#include "parser.h"

bool parseExpenseLine(const std::string& line, Expense& out, std::string& error) {
    // TODO(Parser)
    (void)line; (void)out;
    error = "Not implemented";
    return false;
}

// п.2 — пункт меню
#include "features.h"
#include "input.h"
#include <iostream>

void addFromLine(ExpenseArray& arr, ActionStack& history) {
    // TODO(Parser): readLine -> parseExpenseLine -> arr.push + history.push
    (void)arr; (void)history;
    std::cout << "TODO п.2\n";
}
