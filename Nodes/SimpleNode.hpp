#pragma once

#include <string>

class SimpleNode {
public:
    std::string text;
    int index;
    SimpleNode* next;

    SimpleNode()
        : text(""), next(nullptr), index(1) {}
};