// Owner: Core
#pragma once
#include <iostream>
#include <string>

enum class Category { Food, Transport, Study, Fun, Other };

struct Expense {
    int day = 1;
    Category category = Category::Other;
    double amount = 0.0;
    std::string note;
};

std::string categoryToString(Category c);
bool parseCategory(const std::string& input, Category& outCategory);
bool isValidDay(int day);
bool isValidAmount(double amount);
std::ostream& operator<<(std::ostream& os, const Expense& e);