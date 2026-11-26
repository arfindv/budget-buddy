// Owner: Core
#include "input.h"
#include <iostream>
#include <string>
using namespace std;

int readInt(const string& prompt, int minValue, int maxValue) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);

        if (cin.eof()) {
            cout << "\nВвід закрито.\n";
            return minValue;
        }

        try {
            int value = stoi(line);
            if (value >= minValue && value <= maxValue) {
                return value;
            }
            cout << "Помилка: число має бути від " << minValue
                 << " до " << maxValue << ".\n";
        } catch (...) {
            cout << "Помилка: введіть ціле число.\n";
        }
    }
}

double readDouble(const string& prompt, double minValue) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);

        if (cin.eof()) {
            cout << "\nВвід закрито.\n";
            return minValue;
        }

        try {
            double value = stod(line);
            if (value >= minValue) {
                return value;
            }
            cout << "Помилка: число має бути не менше " << minValue << ".\n";
        } catch (...) {
            cout << "Помилка: введіть число, наприклад 150.50.\n";
        }
    }
}

string readLine(const string& prompt) {
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}