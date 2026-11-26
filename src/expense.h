// Owner: Developer (Core) — struct Expense, enum Category, operator<<
#pragma once
#include <iostream>
#include <string>

enum class Category { Food, Transport, Housing, Entertainment, Health, Other };

struct Expense {
    int id = 0;
    std::string date;      // YYYY-MM-DD
    double amount = 0.0;
    Category category = Category::Other;
    std::string description;
};

std::string categoryToString(Category c);
std::ostream& operator<<(std::ostream& os, const Expense& e);
