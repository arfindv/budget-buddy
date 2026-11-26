# Як працюємо з репозиторієм

1. **Клонуй:** `git clone https://github.com/arfindv/budget-buddy.git`
2. **Свіжий main:** `git checkout main && git pull`
3. **Своя гілка:** `git checkout -b feature/<номер-issue>-коротко` (напр. `feature/5-parser`)
4. **Працюй тільки у своїх файлах** — власник вказаний у першому рядку кожного файлу (`// Owner: ...`).
5. **Перед комітом:** `make` → нуль попереджень.
6. **Коміт і пуш:** `git add . && git commit -m "Parser: розбір рядка" && git push -u origin <гілка>`
7. **PR у main** на GitHub, в описі `Closes #<номер>`. Рев'ю й merge робить Team Lead.
8. **У main напряму не пушимо.**

## Обмеження від викладача (бекенд на C++)
- **Заборонено:** `std::vector`, `std::list`, `std::map`, `std::stack` та інші контейнери STL.
- Колекції — тільки наші: `ExpenseArray` (динамічний масив на `new[]/delete[]`) і `ActionStack` (зв'язний список).
- Дозволено: `std::string`, `iostream`, `fstream`, `iomanip`.
- Перед PR: `grep -rn "vector\|<list>\|<map>\|<stack>" src/` — має бути порожньо.
- Фронтенд (необов'язково) — будь-яка технологія, але вся логіка лишається в C++.

## Хто за що відповідає
| Файл | Власник |
|---|---|
| src/main.cpp, src/search.cpp, README.md | Docs/UX |
| src/expense.*, src/input.*, src/add_manual.cpp | Developer (Core) |
| src/parser.* | Developer (Parser) |
| src/expense_array.*, src/action_stack.*, src/undo.cpp | Developer (Data Structures) |
| src/analytics.* | Developer (Analytics) |
| src/display.cpp, docs/*.pptx | Presenter |
| src/budget.cpp, src/delete.cpp, tests/ | QA Lead |
| docs/specification.md, src/features.h | Team Lead |
