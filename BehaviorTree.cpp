#include "BehaviorTree.hpp"
#include <iostream>
#include <fstream>

//Simple Methods
BehaviorTree::BehaviorTree() {
    root = nullptr;
    answer = false;
}

static void freeTree(TreeNode* node) { //Delete tree
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

BehaviorTree::~BehaviorTree() { //Destructor
    freeTree(root);
}

bool BehaviorTree::isEmpty() { //Checks if the tree is empty
    return root == nullptr;
}

bool BehaviorTree::isLeaf(TreeNode* node) {
    return node != nullptr && node->right == nullptr && node->left == nullptr;
}

//More complex methods
TreeNode* BehaviorTree::insertQuestion(TreeNode* node, std::string question, int index) { //Puts Node in correct position based on index
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

std::string BehaviorTree::makeDecision() { //makeDecision public method overload
    return makeDecision(root);
}

std::string BehaviorTree::makeDecision(TreeNode* node) { //Moves inside the Decision Tree
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

void BehaviorTree::readFile(std::string namefile) { //Reads the file, puts every string into a Node of a Simple List and call setupTree
    std::ifstream fileContent(namefile);
    std::string currentQuestion;
    SimpleList list;
    
    while (std::getline(fileContent, currentQuestion)) {
        list.add(currentQuestion);
    }

    setupTree(list, list.start->index, list.end->index);
}

TreeNode* BehaviorTree::insertQuestion(std::string question, int index) { //Encapsulating insertQuestion
    root = insertQuestion(root, question, index);
    return root;
}

void BehaviorTree::setupTree(SimpleList& list, int start, int end) { //Gets the questions from the list and inserts in the correct order 
    if (start > end) {
        return;
    }

    int middle = start + (end - start) / 2;

    insertQuestion(list.getQuestion(middle), middle);

    setupTree(list, start, middle - 1);
    setupTree(list, middle + 1, end);
}