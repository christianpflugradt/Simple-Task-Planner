#include <ctime>
#include <iostream>
#include <string>
#include "Util.h"

const int dayInSecs = 60 * 60 * 24;

std::string Util::getInput() {
    std::string input;
    getline(std::cin, input);
    return input;
}

void Util::print(std::string str) {
    std::cout << str;
}

void Util::println(std::string str) {
    std::cout << str << "\n\n";
}

int Util::now() {
    return std::time(0);
}

int Util::calcDays(int date) {
    return (Util::now()-date) / dayInSecs;
}

std::string Util::numericString(int limit) {
    std::string result = "";
    for (int i=1; i<=limit; i++) {
        result += std::to_string(i);
    }
    return result;
}
