#pragma once
#include "DoublyNode.hpp"

class RecommendedContentList {
private:
    DoublyNode* head;
    bool correspondsToFilter(const Content& content, const std::string& category) const;

public:
    RecommendedContentList() : head(nullptr) {}

    DoublyNode* getHead() const { return head; }

    void addContent(const Content& content);
    RecommendedContentList filterPerCategory(const std::string& category) const;
    void removeContent(int id);
    void display() const;
};