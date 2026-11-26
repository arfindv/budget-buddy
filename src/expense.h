// Owner: Core
#pragma once
#include <iostream>
#include <string>

enum class Category { Food, Transport, Housing, Entertainment, Health, Other };

struct Expense {
    int id;
    std::string date;
    double amount;
    Category category;
    std::string description;
};

std::string categoryToString(Category c);
bool stringToCategory(const std::string& s, Category& out);
std::ostream& operator<<(std::ostream& os, const Expense& e);