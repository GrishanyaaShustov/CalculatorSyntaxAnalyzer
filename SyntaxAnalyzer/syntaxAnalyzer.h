#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include <iostream>
#include <string>
#include <cstddef>

class SyntaxAnalyzer {
private:
    std::string expr;
    char currentSymbol;
    size_t pos;

    void nextSymbol(); // Переход к следующему символу
    void error(std::string message); // Вывод ошибки и завершение программы
    void expression(); // <Expression> ::= <LogicalAnd> { "|" <LogicalAnd> }
    void logicalAnd(); // <LogicalAnd> ::= <Comparison> { "&" <Comparison> }
    void comparison(); // <Comparison> ::= <Sum> { ("==" | "!=" | "<" | "<=" | ">" | ">=") <Sum> }
    void sum(); // <Sum> ::= <Product> { ("+" | "-") <Product> }
    void product(); // <Product> ::= <Factor> { ("*" | "/") <Factor> }
    void factor(); // <Factor> ::= <Letter> | <Number> | "(" <Expression> ")" | "!" <Factor>
    void number(); // Разбор числа (целого или вещественного)


public:
    void parse(std::string input);  // Запуск парсинга строки
};


#endif //SYNTAXANALYZER_H
