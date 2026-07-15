#pragma once

#include "Nodes/DoublyNode.hpp"
#include "Content.hpp"
#include <string>
#include <iostream>
#include <fstream>

class Search;

class ContentDatabase {
    friend class Search;

private:
    DoublyNode *start;
    int genreCount[11] = {0};
    int typeCount[9]   = {0};

public:
    ContentDatabase();
    ~ContentDatabase();
    bool isEmpty();
    void readSetupFile(std::string filepath);
    void insertContent(Content *newContent);
    void removeContent(int id);
    void loadGenreCounts(const std::string& filepath);
    void saveGenreCounts(const std::string& filepath);
    void loadTypeCounts(const std::string& filepath);
    void saveTypeCounts(const std::string& filepath);
    void incrementGenreCount(Genre genre);
    void incrementTypeCount(ContentType type);
    int getGenreCount(Genre genre);
    int getTypeCount(ContentType type);
    void printAll();
    DoublyNode* getStart() const { return start; }
};