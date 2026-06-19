#pragma once
#include "DoublyNode.hpp"

class RecommendedContentList {
private:
    DoublyNode* head;

public:
    RecommendedContentList() : head(nullptr) {}

    void addContent(const Content& content);
    void removeContent(int id);
    void display() const;
};