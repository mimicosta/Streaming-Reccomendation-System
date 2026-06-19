#pragma once

#include "DoublyNode.hpp"
#include "Content.hpp"

class MostWatchedContentHistory {
private:
    DoublyNode* head;
    DoublyNode* tail;
public:
    MostWatchedContentHistory() : head(nullptr) {}
    void addContent(const Content& content);
    void displayHistory() const;
}