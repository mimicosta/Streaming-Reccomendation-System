#pragma once

#include "TreeNode.hpp"
#include "SimpleList.hpp"
#include <string>

class BehaviorTree {
private:
    TreeNode* root;
    bool answer;

    TreeNode* insertQuestion(TreeNode* node, std::string question, int index);

public:
    BehaviorTree();
    ~BehaviorTree();

    bool isEmpty();
    bool isLeaf(TreeNode* node);
    std::string makeDecision();
    std::string makeDecision(TreeNode* node);
    void readFile(std::string namefile);
    TreeNode* insertQuestion(std::string question, int index);
    void setupTree(SimpleList& list, int start, int end);
};