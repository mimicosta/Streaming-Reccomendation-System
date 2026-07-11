#include "SimpleList.hpp"
#include <iostream>

SimpleList::SimpleList() {
    start = nullptr;
    end = nullptr;
}

SimpleList::~SimpleList() {
    SimpleNode* current = start;
    while (current != nullptr) {
        SimpleNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

bool SimpleList::isEmpty() {
    return (start == nullptr);
}

void SimpleList::add(std::string text) {
    SimpleNode* newNode = new SimpleNode();
    newNode->text = text;

    if (isEmpty()) {
        newNode->index = 1;
        start = newNode;
        end = newNode;
    } else {
        newNode->index = end->index + 1;
        end->next = newNode;
        end = newNode;
    }
}

std::string SimpleList::getQuestion(int index) { 
    SimpleNode* auxNode = start;

    while (auxNode != nullptr && auxNode->index != index) {
        auxNode = auxNode->next;
    }

    if (auxNode != nullptr) {
        return auxNode->text;
    }
    return "";
}