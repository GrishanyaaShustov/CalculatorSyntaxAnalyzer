#include "syntaxAnalyzer.h"
#include <iostream>

int main() {
    SyntaxAnalyzer parser;
    std::string input;
    std::cout << "Enter expression: ";
    std::getline(std::cin, input);
    parser.parse(input);
    return 0;
}