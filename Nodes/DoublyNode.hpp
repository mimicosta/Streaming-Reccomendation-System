#pragma once

#include "Content.hpp"

class DoublyNode
{
public:
    Content content;
    DoublyNode* next;
    DoublyNode* prev;

    DoublyNode(const Content& content)
        : content(content), next(nullptr), prev(nullptr) {}
};