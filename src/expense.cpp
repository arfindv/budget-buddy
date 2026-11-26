// Owner: Developer (Core)
#include "expense.h"

std::string categoryToString(Category c) {
    // TODO(Core)
    (void)c;
    return "Other";
}

std::ostream& operator<<(std::ostream& os, const Expense& e) {
    // TODO(Core)
    return os << e.id;
}
