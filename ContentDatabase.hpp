#pragma once

#include "Nodes/DoublyNode.hpp"
#include "Content.hpp"
#include <string>
#include <iostream>
#include <fstream>

class ContentDatabase{
private:
    DoublyNode start;

public:
    ContentDatabase();
    ~ContentDatabase();
    void readSetupFile(std::string filepath);
    void insertContent(Content newContent);
};