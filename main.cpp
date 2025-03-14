#include "syntaxAnalyzer.h"
#include <iostream>

int main() {
    SyntaxAnalyzer analyzer;
    analyzer.parse("");  // Пример выражения
    analyzer.printPolish(analyzer.getRoot());  // Вывод польской записи
}