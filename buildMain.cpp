#include "buildMain.h"

void runCalculator() {
    std::string expression;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, expression);

    SyntaxAnalyzer analyzer;
    Calculator calculator;

    analyzer.parse(expression);
    TreeNode* root = analyzer.getRoot();
    calculator.inputVariables();

    // Опция для пошаговых вычислений
    char stepOption;
    std::cout << "Do you want to see step-by-step evaluation? (y/n): ";
    std::cin >> stepOption;
    bool stepByStep = (stepOption == 'y' || stepOption == 'Y');

    try {
        // Вычисляем результат (calculate() сам напечатает рез)
        calculator.calculate(root, stepByStep);
    } catch (std::exception ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}
