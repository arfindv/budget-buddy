// Owner: QA Lead
#include <iostream>

#include "features.h"
#include "input.h"

using namespace std;

void deleteExpense(ExpenseArray& arr, ActionStack& history){
    if(arr.size() == 0){
        cout <<"Витрат ще немає."<<endl;
        return;
    }
    for(int i=0; i<arr.size(); i++){
        cout << arr[i]<<endl;
    }
    int id = readInt("Введіть id витрати для видалення (0 = скасувати): ", 0, 1000000);
    if(id == 0){
        cout <<"Видалення скасовано."<<endl;
        return;
    }

    int index=arr.findIndexById(id);
    if(index == -1){
        cout <<"Не знайдено: витрати з id "<< id <<" немає."<<endl;
        return;
    }
    Expense removed = arr[index];
    history.push(Action{ActionType::Delete, removed, index});
    arr.removeAt(index);

    cout <<"Видалено: "<< removed <<endl;
}