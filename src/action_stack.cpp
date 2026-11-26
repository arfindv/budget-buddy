// Owner: Developer (Data Structures)
#include "action_stack.h"

ActionStack::ActionStack() : top_(nullptr) {}
ActionStack::~ActionStack() { /* TODO: звільнити всі вузли */ }
void ActionStack::push(const Action& a) { (void)a; /* TODO */ }
bool ActionStack::pop(Action& out) { (void)out; return false; /* TODO */ }
bool ActionStack::empty() const { return top_ == nullptr; }
