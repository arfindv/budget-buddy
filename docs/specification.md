# Специфікація Budget Buddy — Team D
<!-- Owner: Team Lead -->

**Версія:** 1.0 · 26.11.2026 · **Фінальний дедлайн:** Сб 28.11, 22:00
**Репозиторій:** https://github.com/arfindv/budget-buddy

## 0. Технічні обмеження (погоджено з викладачем)
- Бекенд — **C++17**, тільки вивчені теми: struct, enum, перевантаження операторів, динамічна пам'ять (`new`/`delete`), зв'язний список, рекурсія, робота з рядками.
- **Без `std::vector` та інших контейнерів STL** (`list`, `map`, `set`, `stack`, `queue`, `array`), без `<algorithm>`.
- Дозволено: `std::string`, `<iostream>`, `<iomanip>`, `<fstream>`, `<limits>`, `<cmath>`.
- Збірка `g++ -std=c++17 -Wall -Wextra` — **без жодного попередження**.
- Фронтенд — на вибір команди (повна свобода), **необов'язковий**. Уся логіка лишається в C++.

## 1. Мета
Консольний застосунок для обліку особистих витрат: додавання (двома способами), перегляд, аналітика за категоріями й періодом, пошук, контроль бюджету, видалення та скасування останньої дії.

## 2. Вимоги клієнта (Client Call)
| # | Вимога | Статус |
|---|---|---|
| К1 | Бекенд на C++ з вивчених тем, без `vector` | Підтверджено викладачем |
| К2 | Фронтенд — повна свобода, за бажанням | Підтверджено викладачем |

**Відкриті питання до клієнта:**
- [ ] Чи потрібно зберігати витрати у файл між запусками?
- [ ] Коли й у якому вигляді буде Chaos Card?
- [ ] Формат здачі (посилання на репозиторій / архів) і точний час у неділю.
- [ ] Чи дозволені `std::string` та `<iomanip>` (робоче припущення — так).

## 3. Модель даних
| Поле | Тип | Правила |
|---|---|---|
| `id` | `int` | унікальний, ≥ 1, призначається автоматично (`nextId()`) |
| `date` | `std::string` | формат `РРРР-ММ-ДД`, напр. `2026-11-26` |
| `amount` | `double` | > 0 |
| `category` | `Category` | Food, Transport, Housing, Entertainment, Health, Other |
| `description` | `std::string` | не порожній |

Зберігання: `ExpenseArray` — власний динамічний масив (початкова місткість 4, подвоєння).
Історія дій: `ActionStack` — стек на однозв'язному списку.

## 4. Меню
| Пункт | Дія | Відповідальний | Функція |
|---|---|---|---|
| 1 | Додати витрату по полях | Core | `addManual` |
| 2 | Додати витрату одним рядком | Parser | `addFromLine` |
| 3 | Таблиця всіх витрат | Presenter | `showTable` |
| 4 | Статистика за категоріями (%) | Analytics | `showCategoryStats` |
| 5 | Пошук (за категорією / текстом) | Docs/UX | `searchExpenses` |
| 6 | Найбільша витрата | Presenter | `showLargest` |
| 7 | Бюджет на місяць | QA Lead | `checkBudget` |
| 8 | Сума за період (рекурсія) | Analytics | `showPeriodTotal` |
| 9 | Видалити витрату за id | QA Lead | `deleteExpense` |
| 10 | Скасувати останню дію | Data Structures | `undoLast` |
| 0 | Вихід | Docs/UX | `main` |

Після кожної дії програма повертається в меню. Будь-яке неправильне введення не завершує програму, а показує пояснення й питає знову.

## 5. Формат введення одним рядком (п.2)
```
дата;сума;категорія;опис
2026-11-26;150.50;Food;Обід
```
| Помилка | Повідомлення |
|---|---|
| Не 4 частини | «Помилка: очікується формат дата;сума;категорія;опис» |
| Неправильна дата | «Помилка: дата має бути у форматі РРРР-ММ-ДД» |
| Сума не число або ≤ 0 | «Помилка: сума має бути додатним числом» |
| Невідома категорія | «Помилка: невідома категорія. Доступні: Food, Transport, Housing, Entertainment, Health, Other» |
| Порожній опис | «Помилка: опис не може бути порожнім» |

Розбір — **вручну** через `find(';')` і `substr`.

## 6. Скасування дії (п.10)
- п.1, п.2 після додавання → `push({Add, e, index})`
- п.9 перед видаленням → `push({Delete, e, index})`
- п.10: `pop`; Add → `removeAt(index)`; Delete → `insertAt(index, expense)`; порожній стек → «Немає дій для скасування».

## 7. Граничні випадки
- Порожній список: п.3, 4, 6, 8 → «Витрат ще немає» (без ділення на нуль).
- Видалення неіснуючого id → «Витрату з id N не знайдено».
- Undo без дій → «Немає дій для скасування».
- Букви замість числа в меню / сумі → повідомлення й повторний запит.
- Період, де дата «від» пізніша за «до» → повідомлення про помилку.
- Повний перелік тестів — `tests/test_cases.md` (QA Lead).

## 8. Інтерфейси модулів
Домовленість команди. Зміни — тільки через Team Lead.

### expense.h — Core
```cpp
#pragma once
#include <iostream>
#include <string>

enum class Category { Food, Transport, Housing, Entertainment, Health, Other };

struct Expense {
    int id;                  // 1, 2, 3...
    std::string date;        // "РРРР-ММ-ДД", напр. "2026-11-26"
    double amount;           // > 0
    Category category;
    std::string description;
};

std::string categoryToString(Category c);                      // Category::Food -> "Food"
bool stringToCategory(const std::string& s, Category& out);    // "Food" -> Category::Food; false якщо невідома
std::ostream& operator<<(std::ostream& os, const Expense& e);  // "#1 | 2026-11-26 | 150.50 | Food | Обід"
```

### input.h — Core
```cpp
#pragma once
#include <string>

int readInt(const std::string& prompt, int minValue, int maxValue);  // питає, доки не введуть ціле в межах
double readDouble(const std::string& prompt, double minValue);       // питає, доки не введуть число >= minValue
std::string readLine(const std::string& prompt);                     // читає цілий рядок (getline)
```
Важливо: `readInt`/`readDouble` після успішного читання викликають `cin.ignore(...)` до `'\n'`, щоб наступний `readLine` не прочитав порожній рядок.

### expense_array.h — Data Structures
```cpp
#pragma once
#include "expense.h"

class ExpenseArray {
public:
    ExpenseArray();
    ~ExpenseArray();
    ExpenseArray(const ExpenseArray&) = delete;
    ExpenseArray& operator=(const ExpenseArray&) = delete;

    void push(const Expense& e);                 // додати в кінець
    bool removeAt(int index);                    // false, якщо індекс поза межами
    void insertAt(int index, const Expense& e);  // вставити на позицію (для undo)
    int size() const;
    int findIndexById(int id) const;             // -1, якщо не знайдено
    int nextId() const;                          // max id + 1 (1 для порожнього)
    Expense& operator[](int index);
    const Expense& operator[](int index) const;

private:
    Expense* data_;
    int size_;
    int capacity_;
    void grow();                                 // місткість × 2, копіювання, delete[] старого
};
```

### action_stack.h — Data Structures
```cpp
#pragma once
#include "expense.h"

enum class ActionType { Add, Delete };

struct Action {
    ActionType type;
    Expense expense;   // копія витрати
    int index;         // де вона стояла в масиві (для відновлення після Delete)
};

class ActionStack {
public:
    ActionStack();
    ~ActionStack();    // звільняє всі вузли
    ActionStack(const ActionStack&) = delete;
    ActionStack& operator=(const ActionStack&) = delete;

    void push(const Action& a);
    bool pop(Action& out);   // false, якщо стек порожній
    bool empty() const;

private:
    struct Node { Action value; Node* next; };
    Node* top_;
};
```

### parser.h — Parser
```cpp
#pragma once
#include "expense.h"
#include <string>

// Формат: "2026-11-26;150.50;Food;Обід"  (дата;сума;категорія;опис)
// true — успіх (out заповнено, крім id); false — error містить зрозуміле пояснення
bool parseExpenseLine(const std::string& line, Expense& out, std::string& error);
```

### analytics.h — Analytics
```cpp
#pragma once
#include "expense_array.h"
#include <string>

void showCategoryStats(const ExpenseArray& arr);   // п.4
double sumForPeriodRecursive(const ExpenseArray& arr, int index,
                             const std::string& from, const std::string& to);  // п.8, РЕКУРСІЯ
void showPeriodTotal(const ExpenseArray& arr);     // п.8: питає дати, викликає рекурсію, друкує
```

### Функції пунктів меню (кожна у своєму .cpp, оголошення — у `features.h`, який додає Docs/UX)
```cpp
#pragma once
#include "expense_array.h"
#include "action_stack.h"

void addManual(ExpenseArray& arr, ActionStack& history);     // п.1  Core          add_manual.cpp
void addFromLine(ExpenseArray& arr, ActionStack& history);   // п.2  Parser        parser.cpp
void showTable(const ExpenseArray& arr);                     // п.3  Presenter     display.cpp
void searchExpenses(const ExpenseArray& arr);                // п.5  Docs/UX       search.cpp
void showLargest(const ExpenseArray& arr);                   // п.6  Presenter     display.cpp
void checkBudget(const ExpenseArray& arr);                   // п.7  QA Lead       budget.cpp
void deleteExpense(ExpenseArray& arr, ActionStack& history); // п.9  QA Lead       delete.cpp
void undoLast(ExpenseArray& arr, ActionStack& history);      // п.10 Data Struct.  undo.cpp
```
Правило історії: **п.1 і п.2** після додавання роблять `history.push({ActionType::Add, e, index})`; **п.9** перед видаленням — `history.push({ActionType::Delete, e, index})`. **п.10** бере `pop` і робить протилежне: Add → `removeAt(index)`, Delete → `insertAt(index, expense)`.

---

## 9. Графік
| Віха | Час |
|---|---|
| Блокери: `expense`, `input`, `expense_array` злиті | Чт 23:00 |
| Пункти 1–5, 9 і `action_stack` | Пт 16:00–18:00 |
| Пункти 6, 7, 8, 10 | Пт 20:00–21:00 |
| Усі PR злиті, повна збірка в main | Пт 23:59 |
| Тести й Bug Bounty | Сб 12:00 |
| Баги виправлені | Сб 15:00 |
| Code freeze | Сб 16:00 |
| Презентація, README, регресія | Сб 18:00 |
| Репетиція | Сб 19:00 |
| Фінальна перевірка | Сб 22:00 |

## 10. Chaos Card
_Заповнити, коли буде видана: що змінилось, рішення команди, що зроблено._
