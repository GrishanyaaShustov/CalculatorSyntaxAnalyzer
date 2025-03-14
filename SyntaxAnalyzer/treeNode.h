#include <string>

#ifndef TREENODE_H
#define TREENODE_H

struct TreeNode {
    std::string value;    // Значение (операнд или оператор)
    TreeNode* left;       // Левый узел
    TreeNode* right;      // Правый узел

    TreeNode(std::string val) : value(val), left(nullptr), right(nullptr) {}
};

#endif //TREENODE_H
