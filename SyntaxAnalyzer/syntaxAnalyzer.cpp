#include "syntaxAnalyzer.h"

void SyntaxAnalyzer::nextSymbol() {
    if (pos < expr.size()) {
        currentSymbol = expr[pos++];
    } else {
        currentSymbol = '\0'; // Конец строки
    }
}

void SyntaxAnalyzer::error(std::string message) {
    std::cerr << "Error at position " << pos << ": " << message << "\n"; // Вывод ошибки
    deleteTree(root);  // Очистка дерева при ошибке
    exit(1);
}

void SyntaxAnalyzer::deleteTree(TreeNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

TreeNode* SyntaxAnalyzer::expression() {
    TreeNode* node = logicalAnd();
    while (currentSymbol == '|') {
        char op = currentSymbol;
        nextSymbol();
        TreeNode* right = logicalAnd();
        TreeNode* newNode = new TreeNode(std::string(1, op));
        newNode->left = node;  // Предыдущий узел становится левым дочерним
        newNode->right = right;
        node = newNode;  // Обновляем узел на новый
    }
    return node;
}

TreeNode* SyntaxAnalyzer::logicalAnd() {
    TreeNode* node = comparison();
    while (currentSymbol == '&') {
        char op = currentSymbol;
        nextSymbol();
        TreeNode* right = comparison();
        TreeNode* newNode = new TreeNode(std::string(1, op));
        newNode->left = node;  // Предыдущий узел становится левым дочерним
        newNode->right = right;
        node = newNode;  // Обновляем узел на новый
    }
    return node;
}

TreeNode* SyntaxAnalyzer::comparison() {
    TreeNode* node = sum();
    while (currentSymbol == '=' || currentSymbol == '!' ||
           currentSymbol == '<' || currentSymbol == '>') {
        std::string op(1, currentSymbol);
        nextSymbol();

        if ((op == "<" && currentSymbol == '=') ||
            (op == ">" && currentSymbol == '=') ||
            (op == "!" && currentSymbol == '=')) {
            op += currentSymbol;
            nextSymbol();
            }

        TreeNode* right = sum();
        TreeNode* newNode = new TreeNode(op);
        newNode->left = node;
        newNode->right = right;
        node = newNode;
           }
    return node;
}

TreeNode* SyntaxAnalyzer::sum() {
    TreeNode* node = product();
    while (currentSymbol == '+' || currentSymbol == '-') {
        char op = currentSymbol;
        nextSymbol();
        TreeNode* right = product();
        TreeNode* newNode = new TreeNode(std::string(1, op));
        newNode->left = node;  // Предыдущий узел становится левым дочерним
        newNode->right = right;
        node = newNode;  // Обновляем узел на новый
    }
    return node;
}

TreeNode* SyntaxAnalyzer::product() {
    TreeNode* node = factor();
    while (currentSymbol == '*' || currentSymbol == '/') {
        char op = currentSymbol;
        nextSymbol();
        TreeNode* right = factor();
        TreeNode* newNode = new TreeNode(std::string(1, op));
        newNode->left = node;  // Предыдущий узел становится левым дочерним
        newNode->right = right;
        node = newNode;  // Обновляем узел на новый
    }
    return node;
}

TreeNode* SyntaxAnalyzer::factor() {
    if (std::isalpha(currentSymbol)) {  // Переменная
        TreeNode* node = new TreeNode(std::string(1, currentSymbol));
        nextSymbol();
        return node;
    } else if (std::isdigit(currentSymbol)) {  // Число
        TreeNode* node = number();
        return node;
    } else if (currentSymbol == '(') {  // Выражение в скобках
        nextSymbol();
        TreeNode* node = expression();
        if (currentSymbol == ')') {
            nextSymbol();
            return node;
        } else {
            error("Expected ')'");
        }
    } else if (currentSymbol == '!') {  // Унарный оператор
        nextSymbol();
        TreeNode* node = factor();
        TreeNode* opNode = new TreeNode("!");
        opNode->left = node;
        return opNode;
    } else {
        error("Incorrect symbol: " + std::string(1, currentSymbol));
    }
}

TreeNode* SyntaxAnalyzer::number() {
    std::string num = "";
    while (std::isdigit(currentSymbol)) {
        num += currentSymbol;
        nextSymbol();
    }
    if (currentSymbol == '.') {  // Вещественное число
        num += '.';
        nextSymbol();
        while (std::isdigit(currentSymbol)) {
            num += currentSymbol;
            nextSymbol();
        }
    }
    return new TreeNode(num);  // Создаём узел с числом
}

// Метод для начала парсинга
void SyntaxAnalyzer::parse(std::string input) {
    expr = input;
    pos = 0;
    nextSymbol();
    root = expression();
    if (currentSymbol != '\0') {
        error("Extra characters at the end of the expression");
    } else {
        std::cout << "Expression is valid\n"; // Вывод успешной проверки
    }
}

// Метод для вывода дерева в ПОЛИЗ
void SyntaxAnalyzer::printPolish(TreeNode* node) {
    if (node) {
        // Сначала рекурсивно выводим левое поддерево
        printPolish(node->left);
        // Рекурсивно выводим правое поддерево
        printPolish(node->right);
        // Сначала выводим операнды (переменные или числа), потом операторы
        std::cout << node->value << " ";
    }
}

TreeNode* SyntaxAnalyzer::getRoot() const {
    return root;
}