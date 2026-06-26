#include "MostWatchedContentHistory.hpp"
#include <iostream>

void MostWatchedContentHistory::addContent(const Content& content) {
    // 1. Check if the content is already in the history list
    DoublyNode* current = head;
    DoublyNode* existingNode = nullptr;
    while (current != nullptr) {
        if (current->content.getId() == content.getId()) {
            existingNode = current;
            break;
        }
        current = current->next;
    }

    if (existingNode) {
        existingNode->content = content; 

        if (existingNode == head) {
            return;
        }

        if (existingNode->prev) {
            existingNode->prev->next = existingNode->next;
        }
        if (existingNode->next) {
            existingNode->next->prev = existingNode->prev;
        } else {
            tail = existingNode->prev;
        }

        existingNode->next = nullptr;
        existingNode->prev = nullptr;

        DoublyNode* target = head;
        if (existingNode->content.getViewCount() > target->content.getViewCount()) {
            existingNode->next = target;
            target->prev = existingNode;
            head = existingNode;
            return;
        }

        while (target->next && target->next->content.getViewCount() >= existingNode->content.getViewCount()) {
            target = target->next;
        }

        existingNode->next = target->next;
        existingNode->prev = target;
        if (target->next) {
            target->next->prev = existingNode;
        } else {
            tail = existingNode;
        }
        target->next = existingNode;

    } else {
        DoublyNode* newNode = new DoublyNode(content);

        if (!head) {
            head = newNode;
            tail = newNode;
            return;
        }

        if (newNode->content.getViewCount() > head->content.getViewCount()) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        }

        DoublyNode* target = head;
        while (target->next && target->next->content.getViewCount() >= newNode->content.getViewCount()) {
            target = target->next;
        }

        newNode->next = target->next;
        newNode->prev = target;
        if (target->next) {
            target->next->prev = newNode;
        } else {
            tail = newNode;
        }
        target->next = newNode;
    }
}

void MostWatchedContentHistory::displayHistory() const {
    if (head == nullptr) {
        std::cout << "No viewing history yet.\n";
        return;
    }
    DoublyNode* current = head;
    int rank = 1;
    while (current) {
        std::cout << rank++ << ". " << current->content.getTitle()
                  << " | Type: " << current->content.typeToString(current->content.getType())
                  << " | Genre: " << current->content.genreToString(current->content.getGenre())
                  << " | Views: " << current->content.getViewCount() << std::endl;
        current = current->next;
    }
}