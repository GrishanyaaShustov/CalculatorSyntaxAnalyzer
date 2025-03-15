#include "Calculator.h"
#include <iostream>

double Calculator::getVariableValue(std::string varName) {
    if (variables.find(varName) == variables.end()) {
        throw std::runtime_error("Error: Undefined variable '" + varName + "'.");
    }
    return variables[varName];
}

double Calculator::evaluate(TreeNode *node, bool stepByStep) {
    if (!node) return 0;

    // Если узел - число
    if (std::isdigit(node->value[0]) || (node->value[0] == '-' && node->value.size() > 1)) {
        return std::stod(node->value);
    }

    // Если узел - переменная
    if (std::isalpha(node->value[0])) {
        return getVariableValue(node->value);
    }

    // Унарный оператор "!"
    if (node->value == "!") {
        double operand = evaluate(node->left, stepByStep);
        if (stepByStep) {
            std::cout << "Evaluating: !" << operand << "\n";
        }
        return !operand;
    }

    // Рекурсивно вычисляем подвыражения
    double leftValue = evaluate(node->left, stepByStep);
    double rightValue = evaluate(node->right, stepByStep);

    // Определяем оператор и выполняем соответствующее вычисление
    double result = 0;

    if (node->value == "+") {
        result = leftValue + rightValue;
    } else if (node->value == "-") {
        result = leftValue - rightValue;
    } else if (node->value == "*") {
        result = leftValue * rightValue;
    } else if (node->value == "/") {
        if (rightValue == 0) throw std::runtime_error("Division by zero!");
        result = leftValue / rightValue;
    } else if (node->value == "&") {
        result = leftValue && rightValue;
    } else if (node->value == "|") {
        result = leftValue || rightValue;
    } else if (node->value == "<") {
        result = leftValue < rightValue;
    } else if (node->value == ">") {
        result = leftValue > rightValue;
    } else if (node->value == "=") {
        result = leftValue == rightValue;
    } else if (node->value == "!=") {
        result = leftValue != rightValue;
    } else if (node->value == "<=") {
        result = leftValue <= rightValue;
    } else if (node->value == ">=") {
        result = leftValue >= rightValue;
    } else {
        throw std::runtime_error("Unknown operator: " + node->value);
    }

    // Выводим вычисление, но только если это не лист дерева (число/переменная)
    if (stepByStep) {
        std::cout << "Evaluating: " << leftValue << " " << node->value << " " << rightValue << "\n";
    }

    return result;
}


// Установка значения переменной
void Calculator::setVariableValue(std::string varName, double value) {
    variables[varName] = value;
}

// Вычисление выражения с возможностью пошагового просмотра
double Calculator::calculate(TreeNode *root, bool stepByStep) {
    // Определяем переменные в выражении
    scanVariables(root);

    // Если есть переменные, запрашиваем их значения
    if (!variables.empty()) {
        std::cout << "Your expression contains variables.\n";
        inputVariables();
    }

    // Первое вычисление
    double result = evaluate(root, stepByStep);
    std::cout << "Result: " << result << "\n"; // Единственный раз, когда печатаем результат

    // Цикл для повторного вычисления, но только если есть переменные
    while (!variables.empty()) {
        std::cout << "Do you want to enter new variable values and recalculate? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') break;

        inputVariables();
        result = evaluate(root, stepByStep);
        std::cout << "New result: " << result << "\n";
    }

    return result;
}

// Поиск переменных в дереве выражения
void Calculator::scanVariables(TreeNode *node) {
    if (!node) return;

    // Если узел — переменная
    if (std::isalpha(node->value[0]) && variables.find(node->value) == variables.end()) {
        variables[node->value] = 0; // По умолчанию 0, чтобы потом запросить значение
    }

    scanVariables(node->left);
    scanVariables(node->right);
}

// Ввод значений переменных
void Calculator::inputVariables() {
    for (auto &var: variables) {
        // Тут надо auto& а не auto =))5
        std::cout << "Enter value for '" << var.first << "': ";
        std::cin >> var.second;
    }
}

// Очистка таблицы переменных
void Calculator::clearVariables() {
    variables.clear();
}
