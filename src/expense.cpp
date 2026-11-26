// Owner: Core
#include "expense.h"
#include <iomanip>
using namespace std;

string categoryToString(Category c) {
    if (c == Category::Food) {
        return "Food";
    }
    if (c == Category::Transport) {
        return "Transport";
    }
    if (c == Category::Housing) {
        return "Housing";
    }
    if (c == Category::Entertainment) {
        return "Entertainment";
    }
    if (c == Category::Health) {
        return "Health";
    }
    return "Other";
}

bool stringToCategory(const string& s, Category& out) {
    if (s == "Food") {
        out = Category::Food;
        return true;
    }
    if (s == "Transport") {
        out = Category::Transport;
        return true;
    }
    if (s == "Housing") {
        out = Category::Housing;
        return true;
    }
    if (s == "Entertainment") {
        out = Category::Entertainment;
        return true;
    }
    if (s == "Health") {
        out = Category::Health;
        return true;
    }
    if (s == "Other") {
        out = Category::Other;
        return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const Expense& e) {
    os << "#" << e.id << " | " << e.date << " | ";
    os << fixed << setprecision(2) << e.amount;   
    os << " | " << categoryToString(e.category);
    os << " | " << e.description;
    return os;
}