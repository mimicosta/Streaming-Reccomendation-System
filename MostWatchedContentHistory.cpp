#include "MostWatchedContentHistory.hpp"
#include <iostream>

void MostWatchedContentHistory::addContent(const Content& content) {
    DoublyNode* newNode = new DoublyNode(content);

    if (!head) {
        head = newNode;
        return;
    }

    DoublyNode* current = head;

    while (current &&
           current->content.getViewCount() >= content.getViewCount()) {
        current = current->next;
    }

    if (current == head) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else if (!current) {
        DoublyNode* tail = head;

        while (tail->next) tail = tail->next;

        tail->next = newNode;
        newNode->prev = tail;
    }

    else {
        newNode->next = current;
        newNode->prev = current->prev;

        current->prev->next = newNode;
        current->prev = newNode;
    }
}

void MostWatchedContentHistory::displayHistory() const {
    DoublyNode* current = head;

    while (current) {
        std::cout << "Title: " << current->content.getTitle()
                  << ", Views: " << current->content.getViewCount() << std::endl;
        current = current->next;
    }
}