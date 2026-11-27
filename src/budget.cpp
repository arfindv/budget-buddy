// Owner: QA Lead
#include <iostream>
#include <iomanip>

#include "features.h"
#include "input.h"
using namespace std;

static int toCents(double value){
    return static_cast<int>(value*100.0+0.5);
}
static double totalAmount(const ExpenseArray& arr){
    double sum=0.0;
    for(int i=0; i<arr.size(); i++){
        sum += arr[i].amount;
    }
    return sum;
}
void checkBudget(const ExpenseArray& arr){
    double limit = readDouble("Введіть місячний ліміт (>0): ", 0.01);
    double total = totalAmount(arr);

    if(arr.size() == 0){
        cout <<"Витрат ще немає."<<endl;
    }

    int difference = toCents(limit)-toCents(total);

    cout << fixed << setprecision(2);
    cout <<"Місячний бюджет:   "<< limit <<endl;
    cout <<"Всього витрачено:  "<< total <<endl;
    if(difference<0){
        cout <<"УВАГА: перевищення бюджету на "<< (-difference)/100.0<<endl;
    }else{
        cout <<"У межах бюджету, залишок: "<< difference/100.0<<endl;
    }
}