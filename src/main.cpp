// Owner: Docs/UX — меню, 0. Exit
#include "features.h"
#include "analytics.h"
#include "input.h"
#include <iostream>

static void printMenu() {
    std::cout << "\n===== Budget Buddy =====\n"
                 " 1. Додати витрату (по полях)\n"
                 " 2. Додати витрату одним рядком\n"
                 " 3. Показати всі витрати (таблиця)\n"
                 " 4. Статистика за категоріями (%)\n"
                 " 5. Пошук\n"
                 " 6. Найбільша витрата\n"
                 " 7. Бюджет\n"
                 " 8. Сума за період\n"
                 " 9. Видалити витрату\n"
                 "10. Скасувати останню дію\n"
                 " 0. Вихід\n";
}

int main() {
    ExpenseArray expenses;
    ActionStack history;
    while (true) {
        printMenu();
        int choice = readInt("Ваш вибір: ", 0, 10);
        switch (choice) {
            case 1: addManual(expenses, history); break;
            case 2: addFromLine(expenses, history); break;
            case 3: showTable(expenses); break;
            case 4: showCategoryStats(expenses); break;
            case 5: searchExpenses(expenses); break;
            case 6: showLargest(expenses); break;
            case 7: checkBudget(expenses); break;
            case 8: showPeriodTotal(expenses); break;
            case 9: deleteExpense(expenses, history); break;
            case 10: undoLast(expenses, history); break;
            case 0: std::cout << "До побачення!\n"; return 0;
        }
    }
}
