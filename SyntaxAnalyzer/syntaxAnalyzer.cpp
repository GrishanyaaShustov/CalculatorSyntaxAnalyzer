#include "syntaxAnalyzer.h"

void SyntaxAnalyzer::nextSymbol() {
    if (pos < expr.size()) {
        currentSymbol = expr[pos++];
    } else {
        currentSymbol = '\0';
    }
}

void SyntaxAnalyzer::error(std::string message) {
    std::cerr << "Error in position " << pos << ": " << message << "\n";
    exit(1);
}

void SyntaxAnalyzer::expression() {
    logicalAnd();
    while (currentSymbol == '|') {
        nextSymbol();
        logicalAnd();
    }
}

void SyntaxAnalyzer::logicalAnd() {
    comparison();
    while (currentSymbol == '&') {
        nextSymbol();
        comparison();
    }
}

void SyntaxAnalyzer::comparison() {
    sum();
    while (currentSymbol == '=' || currentSymbol == '!' || currentSymbol == '<' || currentSymbol == '>') {
        char op = currentSymbol;
        nextSymbol();
        if (op == '=' || op == '!') {
            if (currentSymbol == '=') nextSymbol();
            else error("The '=' character was expected after " + std::string(1, op));
        }
        sum();
    }
}

void SyntaxAnalyzer::sum() {
    product();
    while (currentSymbol == '+' || currentSymbol == '-') {
        nextSymbol();
        product();
    }
}

void SyntaxAnalyzer::product() {
    factor();
    while (currentSymbol == '*' || currentSymbol == '/') {
        nextSymbol();
        factor();
    }
}

void SyntaxAnalyzer::factor() {
    if (std::isalpha(currentSymbol)) {
        nextSymbol();
    } else if (std::isdigit(currentSymbol)) {
        number();
    } else if (currentSymbol == '(') {
        nextSymbol();
        expression();
        if (currentSymbol == ')') {
            nextSymbol();
        } else {
            error("Expected ')'");
        }
    } else if (currentSymbol == '!') {
        nextSymbol();
        factor();
    } else {
        error("Incorrect symbol: " + std::string(1, currentSymbol));
    }
}

void SyntaxAnalyzer::number() {
    while (std::isdigit(currentSymbol)) nextSymbol();
    if (currentSymbol == '.') {
        nextSymbol();
        if (!std::isdigit(currentSymbol)) {
            error("The expected digit was after '.'");
        }
        while (std::isdigit(currentSymbol)) nextSymbol();
    }
}

void SyntaxAnalyzer::parse(std::string input) {
    expr = input;
    pos = 0;
    nextSymbol();
    expression();
    if (currentSymbol != '\0') {
        error("Extra characters at the end of the expression");
    } else {
        std::cout << "Expression is correct\n";
    }
}


