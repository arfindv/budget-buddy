#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Підключи тут заголовковий файл вашого проєкту, де описані структури:
// #include "types.h"

// Оголошення функцій (їхній код знаходиться в інших файлах проєкту)

void initExpenses(ExpenseArray& list);
void freeExpenses(ExpenseArray& list);
void initStack(ActionStack& history);
void freeStack(ActionStack& history);

bool parseCategory(const string& input, Category& outCategory);
bool isValidDay(int day);
bool isValidAmount(double amount);

bool addExpense(ExpenseArray& list, ActionStack& history, const Expense& exp);
bool parseExpenseLine(const string& line, Expense& outExp, string& errorMsg);
void printAllExpenses(const ExpenseArray& list);
void printCategorySummary(const ExpenseArray& list);
void searchByNote(const ExpenseArray& list, const string& query);
void printMaxExpense(const ExpenseArray& list);
double getTotalExpenses(const ExpenseArray& list);
double getPeriodSumRecursive(const ExpenseArray& list, int dayA, int dayB, int index);
void printExpensesInPeriod(const ExpenseArray& list, int dayA, int dayB);
bool deleteExpenseByNumber(ExpenseArray& list, ActionStack& history, int number);
bool undoLastAction(ExpenseArray& list, ActionStack& history);

// Допоміжні функції для безпечного вводу в main

void clearInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool readInt(const string& prompt, int& value) {
    cout << prompt;
    if (!(cin >> value)) {
        clearInputStream();
        return false;
    }
    clearInputStream();
    return true;
}

bool readDouble(const string& prompt, double& value) {
    cout << prompt;
    if (!(cin >> value)) {
        clearInputStream();
        return false;
    }
    clearInputStream();
    return true;
}

void printMenu() {
    cout << "\n          МЕНЮ:            \n"
         << "1. Додати витрату (по полях)\n"
         << "2. Додати витрату (одним рядком)\n"
         << "3. Показати всі витрати\n"
         << "4. Витрати по категоріях\n"
         << "5. Пошук витрати за приміткою\n"
         << "6. Найбільша витрата\n"
         << "7. Місячний бюджет\n"
         << "8. Витрати за період днів (від A до B)\n"
         << "9. Видалити витрату за номером\n"
         << "10. Скасувати останню дію\n"
         << "0. Вихід\n"
         << "\n";
}

// Головна функція програми

int main() {
    ExpenseArray expenses;
    ActionStack history;

    initExpenses(expenses);
    initStack(history);

    double monthlyBudget = 0.0;
    bool isRunning = true;

    cout << fixed << setprecision(2);

    while (isRunning) {
        printMenu();

        int choice = -1;
        if (!readInt("Оберіть пункт меню (0-10): ", choice)) {
            cout << "Помилка. Некоректний ввід. Введіть число від 0 до 10.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                Expense exp;
                string catStr;

                if (!readInt("Введіть день місяця (1-31): ", exp.day) || !isValidDay(exp.day)) {
                    cout << "Помилка. День має бути цілим числом від 1 до 31.\n";
                    break;
                }

                cout << "Введіть категорію (FOOD, TRANSPORT, STUDY, FUN, OTHER): ";
                getline(cin, catStr);
                if (!parseCategory(catStr, exp.category)) {
                    cout << "Помилка. Невідома категорія: \"" << catStr << "\".\n";
                    break;
                }

                if (!readDouble("Введіть суму: ", exp.amount) || !isValidAmount(exp.amount)) {
                    cout << "Помилка. Сума має бути додатним числом.\n";
                    break;
                }

                cout << "Введіть примітку (латиницею): ";
                getline(cin, exp.note);
                if (exp.note.empty()) {
                    cout << "Помилка. Примітка не може бути порожньою.\n";
                    break;
                }

                if (addExpense(expenses, history, exp)) {
                    cout << "Витрату успішно додано.\n";
                } else {
                    cout << "Помилка. Не вдалося додати витрату.\n";
                }
                break;
            }

            case 2: {
                string line;
                cout << "Введіть рядок (формат: день категорія сума примітка):\n> ";
                getline(cin, line);

                Expense exp;
                string errorMsg;
                if (!parseExpenseLine(line, exp, errorMsg)) {
                    cout << "[Помилка] " << errorMsg << "\n";
                } else {
                    if (addExpense(expenses, history, exp)) {
                        cout << "Витрату успішно додано.\n";
                    } else {
                        cout << "Помилка. Не вдалося додати витрату.\n";
                    }
                }
                break;
            }

            case 3: {
                printAllExpenses(expenses);
                break;
            }

            case 4: {
                printCategorySummary(expenses);
                break;
            }

            case 5: {
                string query;
                cout << "Введіть текст для пошуку в примітці (латиницею): ";
                getline(cin, query);

                if (query.empty()) {
                    cout << "Помилка. Пошуковий запит не може бути порожнім.\n";
                } else {
                    searchByNote(expenses, query);
                }
                break;
            }

            case 6: {
                printMaxExpense(expenses);
                break;
            }

            case 7: {
                double limit = 0.0;
                if (!readDouble("Введіть місячний ліміт бюджету: ", limit) || limit < 0.0) {
                    cout << "Помилка. Ліміт бюджету не може бути від'ємним.\n";
                    break;
                }

                monthlyBudget = limit;
                double total = getTotalExpenses(expenses);
                double diff = monthlyBudget - total;

                cout << "Всього витрачено: " << total << "\n";
                if (diff >= 0.0) {
                    cout << "Статус: У межах бюджету. Залишок: " << diff << "\n";
                } else {
                    cout << "Статус: Перевищення бюджету на: " << -diff << "\n";
                }
                break;
            }

            case 8: {
                int dayA = 0;
                int dayB = 0;

                if (!readInt("Введіть початковий день (1-31): ", dayA) || !isValidDay(dayA)) {
                    cout << "Помилка. Некоректний початковий день.\n";
                    break;
                }
                if (!readInt("Введіть кінцевий день (1-31): ", dayB) || !isValidDay(dayB)) {
                    cout << "Помилка. Некоректний кінцевий день.\n";
                    break;
                }
                if (dayA > dayB) {
                    cout << "Помилка. Початковий день не може бути більшим за кінцевий день.\n";
                    break;
                }

                printExpensesInPeriod(expenses, dayA, dayB);
                double periodSum = getPeriodSumRecursive(expenses, dayA, dayB, 0);
                cout << "Загальна сума за дні " << dayA << "-" << dayB << ": " << periodSum << "\n";
                break;
            }

            case 9: {
                int num = 0;
                if (!readInt("Введіть номер витрати для видалення: ", num) || num <= 0) {
                    cout << "Помилка. Введіть коректний додатний номер.\n";
                    break;
                }

                if (deleteExpenseByNumber(expenses, history, num)) {
                    cout << "Витрату №" << num << " видалено.\n";
                } else {
                    cout << "Помилка. Витрату №" << num << " не знайдено.\n";
                }
                break;
            }

            case 10: {
                if (undoLastAction(expenses, history)) {
                    cout << "Останню дію скасовано.\n";
                } else {
                    cout << "Немає дій для скасування.\n";
                }
                break;
            }

            case 0: {
                cout << "Закінчення програми\n";
                isRunning = false;
                break;
            }

            default: {
                cout << "Помилка. Невідомий пункт меню. Оберіть число від 0 до 10.\n";
                break;
            }
        }
    }

    freeExpenses(expenses);
    freeStack(history);
}