// Owner: Core
#include "expense.h"

static std::string toUpperText(const std::string& text) {
    std::string result = text;
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] >= 'a' && result[i] <= 'z') {
            result[i] = result[i] - 'a' + 'A';
        }
    }
    return result;
}

std::string categoryToString(Category c) {
    switch (c) {
        case Category::Food:      return "FOOD";
        case Category::Transport: return "TRANSPORT";
        case Category::Study:     return "STUDY";
        case Category::Fun:       return "FUN";
        case Category::Other:     return "OTHER";
    }
    return "OTHER";
}

bool parseCategory(const std::string& input, Category& outCategory) {
    std::string word = toUpperText(input);

    if (word == "FOOD") {
        outCategory = Category::Food;
    } else if (word == "TRANSPORT") {
        outCategory = Category::Transport;
    } else if (word == "STUDY") {
        outCategory = Category::Study;
    } else if (word == "FUN") {
        outCategory = Category::Fun;
    } else if (word == "OTHER") {
        outCategory = Category::Other;
    } else {
        return false;
    }
    return true;
}

bool isValidDay(int day) {
    return day >= 1 && day <= 31;
}

bool isValidAmount(double amount) {
    return amount > 0.0;
}

std::ostream& operator<<(std::ostream& os, const Expense& e) {
    os << e.day << " | "
       << categoryToString(e.category) << " | "
       << e.amount << " | "
       << e.note;
    return os;
}