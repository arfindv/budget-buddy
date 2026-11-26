// Owner: Developer (Data Structures) — стек дій на зв'язному списку
#pragma once
#include "expense.h"

enum class ActionType { Add, Delete };

struct Action {
    ActionType type;
    Expense expense;
    int index;
};

class ActionStack {
public:
    ActionStack();
    ~ActionStack();
    ActionStack(const ActionStack&) = delete;
    ActionStack& operator=(const ActionStack&) = delete;

    void push(const Action& a);
    bool pop(Action& out);
    bool empty() const;

private:
    struct Node { Action value; Node* next; };
    Node* top_;
};
