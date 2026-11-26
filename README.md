# Budget Buddy — Team D

Консольний трекер витрат на C++.

## Збірка й запуск
```bash
make        # g++ -std=c++17 -Wall -Wextra -pedantic
./budget-buddy
```

## Команда
| Роль | Ім'я | Функції меню |
|---|---|---|
| Team Lead | | — |
| Developer (Core) | | П.1 |
| Developer (Parser) | | П.2 |
| Developer (Data Structures) | | П.10 |
| Developer (Analytics) | | П.4, П.8 |
| QA Lead | | П.7, П.9 |
| Presenter | | П.3, П.6 |
| Docs/UX | | Меню, П.5 |

## Evidence Table
<!-- Owner: Docs/UX. Для кожної вимоги — де вона в коді й чим підтверджена -->
| # | Вимога | Файл / функція | Доказ (скриншот / тест) | Статус |
|---|---|---|---|---|
| 1 | Додавання по полях | src/add_manual.cpp `addManual` | | ⬜ |
| 2 | Введення одним рядком | src/parser.cpp `parseExpenseLine` | | ⬜ |
| 3 | Таблиця витрат | src/display.cpp `showTable` | | ⬜ |
| 4 | Категорії та % | src/analytics.cpp `showCategoryStats` | | ⬜ |
| 5 | Пошук | src/search.cpp `searchExpenses` | | ⬜ |
| 6 | Найбільша витрата | src/display.cpp `showLargest` | | ⬜ |
| 7 | Бюджет | src/budget.cpp `checkBudget` | | ⬜ |
| 8 | Період (рекурсія) | src/analytics.cpp `sumForPeriodRecursive` | | ⬜ |
| 9 | Видалення | src/delete.cpp `deleteExpense` | | ⬜ |
| 10 | Скасування дії | src/undo.cpp `undoLast` | | ⬜ |
| — | struct, enum, operator<< | src/expense.h | | ⬜ |
| — | Динамічний масив | src/expense_array.h | | ⬜ |
| — | Стек на зв'язному списку | src/action_stack.h | | ⬜ |
| — | Безпечне введення | src/input.h | | ⬜ |
| — | Збірка без попереджень -Wall -Wextra | Makefile | | ⬜ |

## Як працюємо
1. Береш свою Issue, ставиш собі assignee.
2. Гілка від `main`: `feature/<номер-issue>-коротко`, напр. `feature/3-expense-array`.
3. `make` має збиратися **без жодного warning**.
4. PR у `main` з `Closes #<номер>` в описі → рев'ю Team Lead → merge.
5. У `main` напряму не пушимо.
