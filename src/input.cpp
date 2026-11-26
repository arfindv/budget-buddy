// Owner: Developer (Core)
#include "input.h"
#include <iostream>
#include <limits>

int readInt(const std::string& prompt, int minValue, int maxValue) {
    // TODO(Core): перевірка cin.fail(), діапазону, очищення буфера
    (void)prompt; (void)minValue; (void)maxValue;
    return 0;
}

double readDouble(const std::string& prompt, double minValue) {
    // TODO(Core)
    (void)prompt; (void)minValue;
    return 0.0;
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}
