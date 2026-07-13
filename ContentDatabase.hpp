#pragma once

#include "Nodes/DoublyNode.hpp"
#include "Content.hpp"
#include <string>
#include <iostream>
#include <fstream>

class ContentDatabase{
private:
    DoublyNode *start;

public:
    ContentDatabase();
    ~ContentDatabase();
    bool isEmpty();
    void readSetupFile(std::string filepath);
    void insertContent(Content *newContent);
    void removeContent(int id);
    void printAll();
    DoublyNode* getStart() const { return start; }
};