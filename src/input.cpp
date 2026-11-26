// Owner: Core
#include "input.h"
#include <iostream>
#include <limits>

using namespace std;

int readInt(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Помилка. Введіть ціле число від " << minValue
             << " до " << maxValue << ".\n";
    }
}

double readDouble(const string& prompt, double minValue) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Помилка. Введіть число не менше " << minValue << ".\n";
    }
}

string readLine(const string& prompt) {
    string line;
    cout << prompt;
    getline(cin, line);
    return line;
}