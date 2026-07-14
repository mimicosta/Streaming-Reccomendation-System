#pragma once

#include "SearchTreeNode.hpp"
#include "ContentDatabase.hpp"
#include <vector>
#include <string>

class Search {
private:
    SearchTreeNode* root;

    SearchTreeNode* insertInTree(SearchTreeNode* node, Content* content);
    void searchInTree(SearchTreeNode* node, const std::string& prefix, std::vector<Content*>& results, int limit);
    void destroyTree(SearchTreeNode* node);
    std::string toLower(std::string str);
    bool matchesPrefix(std::string title, std::string prefix);

public:
    Search();
    ~Search();
    void buildFromDatabase(ContentDatabase& db);
    void autoComplete(const std::string& prefix);
    std::vector<Content*> search(const std::string& prefix, int limit = 5);
};