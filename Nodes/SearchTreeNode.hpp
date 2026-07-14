#pragma once
#include "../Content.hpp"

class SearchTreeNode {
public:
    Content* content; 
    SearchTreeNode* left;
    SearchTreeNode* right;

    SearchTreeNode(Content* content)
        : content(content), left(nullptr), right(nullptr) {}
};