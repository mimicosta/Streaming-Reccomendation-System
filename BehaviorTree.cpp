#include "BehaviorTree.hpp"
#include <iostream>
#include <fstream>

BehaviorTree::BehaviorTree() {
    root = nullptr;
    answer = false;
}

static void freeTree(TreeNode* node) {
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

BehaviorTree::~BehaviorTree() {
    freeTree(root);
}

TreeNode* BehaviorTree::insertQuestion(TreeNode* node, std::string question, int index) {
    if (node == nullptr) {
        return new TreeNode(question, index);
    }
    if (index < node->index) {
        node->left = insertQuestion(node->left, question, index);
    } else if (index > node->index) {
        node->right = insertQuestion(node->right, question, index);
    }
    return node;
}

bool BehaviorTree::isEmpty() {
    return root == nullptr;
}

bool BehaviorTree::isLeaf(TreeNode* node) {
    return node != nullptr && node->right == nullptr && node->left == nullptr;
}

std::string BehaviorTree::makeDecision() {
    return makeDecision(root);
}

std::string BehaviorTree::makeDecision(TreeNode* node) {
    if (node == nullptr) {
        return "";
    }

    if (isLeaf(node)) {
        return node->question;
    }

    std::cout << node->question << std::endl;
    std::cin >> answer;

    if (answer) {
        return makeDecision(node->right);
    } else {
        return makeDecision(node->left);
    }
}

void BehaviorTree::readFile(std::string namefile) {
    std::ifstream fileContent(namefile);
    std::string currentQuestion;
    SimpleList list;
    
    while (std::getline(fileContent, currentQuestion)) {
        list.add(currentQuestion);
    }

    setupTree(list, list.start->index, list.end->index);
}

TreeNode* BehaviorTree::insertQuestion(std::string question, int index) {
    root = insertQuestion(root, question, index);
    return root;
}

void BehaviorTree::setupTree(SimpleList& list, int start, int end) { 
    if (start > end) {
        return;
    }

    int middle = start + (end - start) / 2;

    insertQuestion(list.getQuestion(middle), middle);

    setupTree(list, start, middle - 1);
    setupTree(list, middle + 1, end);
}