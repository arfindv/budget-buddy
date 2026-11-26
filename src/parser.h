// Owner: Developer (Parser) — п.2: введення одним рядком
#pragma once
#include "expense.h"
#include <string>

// Формат (узгодити в specification.md), напр.: 2026-11-26;150.50;Food;Обід
// Повертає true при успіху, інакше false і пояснення в error.
bool parseExpenseLine(const std::string& line, Expense& out, std::string& error);
