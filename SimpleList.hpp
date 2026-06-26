#pragma once 

#include "Nodes/SimpleNode.hpp"
#include <string>

class SimpleList {
private:
    SimpleNode* start;
    SimpleNode* end;

public:
    SimpleList();
    ~SimpleList();
    bool isEmpty();
    void add(std::string text);
    std::string getQuestion(int index);

    friend class BehaviorTree;
};
