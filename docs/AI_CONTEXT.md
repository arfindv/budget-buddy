# Budget Buddy — контекст проєкту для Claude

> **Як користуватись (для учасника команди):** відкрий новий чат із Claude, прикріпи цей файл і напиши:
> «Я — <твоя роль>. Що мені робити зараз?»
> Якщо щось не працює — встав у той самий чат текст помилки повністю.

---

## Інструкції для Claude

Ти допомагаєш студенту з команди Team D, яка до суботи 28.11 пише навчальний проєкт на C++. Дотримуйся цього:

1. **Спершу дізнайся роль** користувача (якщо він її не назвав) і його ОС (Windows / Mac). Далі допомагай **тільки з його задачами** з розділу «Ролі та задачі».
2. **Рівень — початківець.** Пояснюй покроково, простими словами, українською. Кожен новий термін — одним реченням.
3. **Студент має розуміти свій код**, бо захищатиме його усно. Пиши код із коментарями до кожного важливого рядка, а після коду — 3–5 питань, які можуть поставити на захисті, з короткими відповідями. Якщо частину коду можна залишити студенту як просту вправу за зразком — так і зроби, і скажи про це.
4. **Жорсткі обмеження коду** (див. розділ «Технічні правила») — ніколи їх не порушуй, навіть якщо студент просить. Зокрема: **жодних `std::vector` та інших контейнерів STL**.
5. **Не змінюй чужі файли й інтерфейси.** Сигнатури функцій з розділу «Інтерфейси» — це домовленість команди. Якщо здається, що її треба змінити, — порадь написати Team Lead.
6. **Завжди закінчуй відповідь** тим, як перевірити результат (що ввести, що має вивестись) і як здати роботу (git-команди, PR).
7. Нагадуй про дедлайн задачі, якщо він сьогодні.
8. Якщо задача залежить від ще не готового файлу іншого учасника — поясни, як тимчасово працювати без нього (заглушка), і не пиши чужий файл замість нього.

---

## Про проєкт

**Budget Buddy** — консольний трекер витрат на C++. Користувач бачить меню, обирає пункт, програма виконує дію й повертається в меню.

```
===== Budget Buddy =====
 1. Додати витрату (по полях)
 2. Додати витрату одним рядком
 3. Показати всі витрати (таблиця)
 4. Статистика за категоріями (%)
 5. Пошук
 6. Найбільша витрата
 7. Бюджет
 8. Сума за період (рекурсія)
 9. Видалити витрату
10. Скасувати останню дію
 0. Вихід
```

- Репозиторій: https://github.com/arfindv/budget-buddy
- Фінальний дедлайн: **субота 28.11, 22:00**
- Викладач: бекенд — **C++ тільки з вивчених тем, без `vector`**. Фронтенд — за бажанням, будь-яка технологія (необов'язковий бонус).

---

## Технічні правила

- Стандарт **C++17**, компілятор `g++`, прапорці **`-Wall -Wextra`** — збірка має бути **без жодного warning**.
- ❌ Заборонено: `std::vector`, `std::list`, `std::map`, `std::set`, `std::stack`, `std::queue`, `std::array` та будь-які інші контейнери STL; `<algorithm>`.
- ✅ Дозволено: `std::string`, `<iostream>`, `<iomanip>`, `<fstream>`, `<limits>`, `<cmath>`, звичайні масиви, `new`/`delete`.
- Колекції — тільки наші власні: `ExpenseArray` (динамічний масив) і `ActionStack` (стек на зв'язному списку).
- Кожен файл починається з рядка `// Owner: <роль>`.
- Кожен заголовок починається з `#pragma once`.
- Перевірка перед PR: `grep -rn "vector" src/` нічого не знаходить.

---

## Структура репозиторію

```
budget-buddy/
├── src/
│   ├── main.cpp                ← Docs/UX (меню, 0. Exit)
│   ├── expense.h/.cpp          ← Core (struct, enum, operator<<)
│   ├── input.h/.cpp            ← Core (безпечне введення)
│   ├── add_manual.cpp          ← Core (п.1)
│   ├── parser.h/.cpp           ← Parser (п.2)
│   ├── expense_array.h/.cpp    ← Data Structures (динамічний масив)
│   ├── action_stack.h/.cpp     ← Data Structures (стек)
│   ├── undo.cpp                ← Data Structures (п.10)
│   ├── analytics.h/.cpp        ← Analytics (п.4, п.8)
│   ├── display.cpp             ← Presenter (п.3, п.6)
│   ├── search.cpp              ← Docs/UX (п.5)
│   ├── budget.cpp              ← QA Lead (п.7)
│   └── delete.cpp              ← QA Lead (п.9)
├── tests/test_cases.md         ← QA Lead
├── docs/
│   ├── specification.md        ← Team Lead
│   ├── screenshots/            ← скриншоти для Evidence Table
│   └── team_presentation_BudgetBuddy_TeamD_<Група>.pptx ← Presenter
├── README.md                   ← Docs/UX (Evidence Table)
├── CONTRIBUTING.md             ← правила роботи
└── Makefile
```

---

## Інтерфейси (домовленість команди — не змінювати без Team Lead)

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

## Ролі та задачі

Дні: **Чт 26.11 · Пт 27.11 · Сб 28.11**. Фінал — **субота 28.11, 22:00**. 🔴 — блокує інших, запізнюватись не можна.

### Team Lead
- Чт 16:00 — Client Call, учасники в Collaborators, захист гілки main
- Чт 22:00 — `docs/specification.md`
- Пт 23:00 — рев'ю й злиття PR
- 🔴 Пт 23:59 — усі PR злиті, повна збірка в main
- 🔴 Сб 16:00 — code freeze (далі лише критичні фікси)
- 🔴 Сб 22:00 — фінальна перевірка
- Demo Day: розповідає, що з вимог виконано, і про Chaos Card

### Developer (Core)
- 🔴 Чт 20:00 — `expense.h/.cpp`: struct, enum, `categoryToString`, `stringToCategory`, `operator<<`
- 🔴 Чт 23:00 — `input.h/.cpp`: `readInt`, `readDouble`, `readLine` (букви, від'ємні, поза межами → повідомлення й повторний запит)
- Пт 16:00 — **п.1** `add_manual.cpp`: `addManual` — питає дату, суму, категорію (вибір 1–6 через `readInt`), опис; `id = arr.nextId()`; `push`; запис у history
- Захист: struct, enum class, перевантаження оператора, обробка помилок введення

### Developer (Parser)
- Чт — підготовка: перелік неправильних рядків і тексти помилок
- Пт 18:00 — **п.2** `parser.h/.cpp`: `parseExpenseLine` — **вручну** через `find(';')` і `substr`, без `stringstream`-розбиття та регулярок. Перевірки: рівно 4 частини; дата формату `РРРР-ММ-ДД`; сума — число > 0 (`std::stod` у `try/catch`); категорія відома (`stringToCategory`); опис не порожній. `addFromLine`: `readLine` → парсинг → при помилці друкує `error` → при успіху `id`, `push`, history
- Захист: як працюють `find`/`substr`, як обробляються помилки

### Developer (Data Structures)
- 🔴 Чт 23:00 — `expense_array.h/.cpp`: динамічний масив на `new[]`/`delete[]`, початкова місткість 4, `grow()` подвоює
- Пт 16:00 — `action_stack.h/.cpp`: стек на однозв'язному списку
- Пт 21:00 — **п.10** `undo.cpp`: `undoLast` (якщо стек порожній — «Немає дій для скасування»)
- Захист: чим динамічний масив відрізняється від статичного, як працює `grow`, що таке вузол і вказівник `next`, чому деструктор звільняє пам'ять

### Developer (Analytics)
- Чт — підготовка: план п.4 і п.8 у `docs/analytics_notes.md`
- Пт 18:00 — **п.4** `showCategoryStats`: `double sums[6]`, сума по категоріях, відсоток від загальної, таблиця через `iomanip`; порожній масив → «Витрат ще немає» (без ділення на нуль)
- Пт 21:00 — **п.8** `sumForPeriodRecursive` (база: `index == arr.size()` → 0; крок: поточна, якщо дата в межах, + виклик для `index + 1`) і `showPeriodTotal`. Дати порівнюються як рядки
- Сб 14:00 — пояснення рекурсії для захисту (база, крок, приклад на 3 витратах)

### QA Lead
- Чт 23:00 — `tests/test_cases.md`: таблиця `ID | Пункт | Що вводимо | Що має статись | Результат`, мінімум 3 тести на кожен пункт (правильне, неправильне, граничне), разом ≥ 30
- Пт 18:00 — **п.9** `delete.cpp`: `deleteExpense` — питає id, `findIndexById`, якщо -1 → «Не знайдено», інакше запис у history і `removeAt`
- Пт 20:00 — **п.7** `budget.cpp`: `checkBudget` — питає ліміт на місяць (`readDouble`), рахує витрати, показує залишок або попередження про перевищення
- Сб 12:00 — прогін усіх тестів, перевірка `-Wall -Wextra`, Bug Bounty (баги — як Issues з міткою `bug`)
- Сб 18:00 — фінальний регресійний прогін

### Presenter
- Чт 23:00 — `docs/presentation_plan.md`: план 5 слайдів і сценарій демо
- Пт 16:00 — **п.3** `display.cpp`: `showTable` — таблиця з заголовком і вирівняними колонками (`std::setw`, `std::left`, `std::fixed`, `std::setprecision(2)`); порожньо → «Витрат ще немає»
- Пт 20:00 — **п.6** `showLargest`: пошук максимуму лінійним проходом
- Сб 14:00 — чернетка презентації
- Сб 18:00 — скриншоти з фінальної версії, `.pptx` у `docs/`

### Docs/UX
- Чт 22:00 — `src/main.cpp`: меню в циклі `while(true)` + `switch`, 0 — вихід; поки функцій немає — `"Ще в розробці"`. Також `src/features.h` з оголошеннями функцій меню (див. «Інтерфейси»)
- Пт 18:00 — **п.5** `search.cpp`: `searchExpenses` — підменю: за категорією / за текстом в описі (`description.find(text) != std::string::npos`); нічого не знайдено → повідомлення. Уніфікувати тексти помилок у всій програмі
- Сб 14:00 — чернетка `README.md` з Evidence Table
- Сб 18:00 — фінальний README: для кожної вимоги — файл/функція + скриншот

### Усі
- Сб 15:00 — виправити баги від QA
- Сб 19:00–20:00 — репетиція демо й захисту

---

## Як працювати з git

```bash
git clone https://github.com/arfindv/budget-buddy.git
cd budget-buddy
git checkout main && git pull                 # завжди починай зі свіжого main
git checkout -b feature/<роль>-<що-робиш>      # напр. feature/core-expense
# ... пишеш код ...
git add .
git commit -m "Core: struct Expense і operator<<"
git push -u origin feature/<роль>-<що-робиш>
```
Далі на GitHub: **Compare & pull request** → в описі `Closes #<номер Issue>` → **Create pull request**. Рев'ю й merge робить Team Lead. **У main напряму не пушимо.**

Якщо твій код залежить від чужого файлу, який уже злито: `git checkout main && git pull`, потім `git checkout <твоя-гілка> && git merge main`.

Задачі з дедлайнами — в Issues репозиторію, фільтр за міткою ролі: `core`, `parser`, `data-structures`, `analytics`, `qa`, `presenter`, `docs-ux`, `team-lead`.

---

## Збірка й запуск

### Mac
Один раз: `xcode-select --install`
```bash
make
./budget-buddy
```

### Windows (PowerShell)
Один раз:
```powershell
winget install Git.Git
winget install BrechtSanders.WinLibs.POSIX.UCRT
```
Після встановлення — **перезапустити PowerShell**.
```powershell
chcp 65001
g++ -std=c++17 -Wall -Wextra (Get-ChildItem src\*.cpp) -o budget-buddy.exe
.\budget-buddy.exe
```

### Поки не всі файли готові
Збірка всього проєкту впаде, якщо `main.cpp` викликає ще не написані функції. Щоб перевірити свій код окремо — зроби тимчасовий файл **поза `src/`**, напр. `scratch/test_my.cpp`, з власним `main()`, і збери тільки потрібні файли:
```bash
g++ -std=c++17 -Wall -Wextra -Isrc scratch/test_my.cpp src/expense.cpp -o test_my
```
Папку `scratch/` не комітимо.

---

## Типові помилки

| Помилка | Причина / що робити |
|---|---|
| `g++ is not recognized` | Не перезапустив PowerShell після встановлення |
| `fatal: not a git repository` | Ти не в папці проєкту → `cd budget-buddy` |
| `403` / `Permission denied` при push | Не прийняв запрошення в репозиторій (пошта або github.com/notifications) |
| `undefined reference to ...` | Функція оголошена, але її .cpp не потрапив у збірку або ще не написаний |
| `multiple definition of ...` | Функція написана в .h замість .cpp, або один .cpp підключено через `#include` |
| Кракозябри замість українських літер (Windows) | `chcp 65001` перед запуском |
| Після введення числа `getline` читає порожній рядок | Не викликано `cin.ignore(...)` після `cin >>` |
| Програма зациклюється після введення букв | Немає `cin.clear()` + `cin.ignore(...)` після `cin.fail()` |
