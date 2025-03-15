#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include <iostream>
#include <string>
#include <cstddef>
#include "treeNode.h"

class SyntaxAnalyzer {
private:
    std::string expr;
    char currentSymbol;
    size_t pos;
    TreeNode *root; // Корень дерева

    void nextSymbol(); // Переход к следующему символу
    void error(std::string message); // Вывод ошибки и завершение программы
    void deleteTree(TreeNode *node); // Удаление дерева при возникновении ошибки
    TreeNode *expression(); // <Expression> ::= <LogicalAnd> { "|" <LogicalAnd> }
    TreeNode *logicalAnd(); // <LogicalAnd> ::= <Comparison> { "&" <Comparison> }
    TreeNode *comparison(); // <Comparison> ::= <Sum> { ("==" | "!=" | "<" | "<=" | ">" | ">=") <Sum> }
    TreeNode *sum(); // <Sum> ::= <Product> { ("+" | "-") <Product> }
    TreeNode *product(); // <Product> ::= <Factor> { ("*" | "/") <Factor> }
    TreeNode *factor(); // <Factor> ::= <Letter> | <Number> | "(" <Expression> ")" | "!" <Factor>
    TreeNode *number(); // Разбор числа (целого или вещественного)

public:
    void parse(std::string input); // Запуск парсинга строки
    void printPolish(TreeNode *node); // Вывод польской записи (ПОЛИЗ)
    TreeNode *getRoot() const; // Метод для получения корня дерева
};

#endif //SYNTAXANALYZER_H
