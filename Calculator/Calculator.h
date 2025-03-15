#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "treeNode.h"
#include <unordered_map>
#include <string>

class Calculator {
private:
    std::unordered_map<std::string, double> variables; // Таблица значений переменных

    // Получение значения переменной
    double getVariableValue(std::string varName);

    // Рекурсивная функция вычисления выражения
    double evaluate(TreeNode* node, bool stepByStep = false);

    // Сканирование переменных в дереве
    void scanVariables(TreeNode* node);

public:
    // Установка значений переменных
    void setVariableValue(std::string varName, double value);

    // Вычисление выражения
    double calculate(TreeNode* root, bool stepByStep = false);

    // Ввод значений переменных (если есть)
    void inputVariables();

    // Очистка переменных
    void clearVariables();
};

#endif // CALCULATOR_H
