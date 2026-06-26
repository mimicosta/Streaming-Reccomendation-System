#pragma once

#include <string>

class TreeNode
{
public:
    int index;
    std::string question;
    TreeNode* right;
    TreeNode* left;

    TreeNode(const std::string question, const int index)
        : question(question), right(nullptr), left(nullptr), index(index) {}
};