#include "Search.hpp"
#include <iostream>
#include <algorithm>

Search::Search() {
    root = nullptr;
}

Search::~Search() {
    destroyTree(root);
}

std::string Search::toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool Search::matchesPrefix(std::string title, std::string prefix) {
    if (prefix.size() > title.size()) return false;
    return toLower(title).compare(0, prefix.size(), toLower(prefix)) == 0;
}

SearchTreeNode* Search::insertInTree(SearchTreeNode* node, Content* content) {
    if (node == nullptr) {
        return new SearchTreeNode(content);
    }

    if (toLower(content->getTitle()) < toLower(node->content->getTitle())) {
        node->left = insertInTree(node->left, content);
    } else {
        node->right = insertInTree(node->right, content);
    }

    return node;
}

void Search::destroyTree(SearchTreeNode* node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

void Search::buildFromDatabase(ContentDatabase& db) {
    if (root != nullptr) {
        destroyTree(root);
        root = nullptr;
    }

    // Acessando diretamente o start privado através de friend class
    DoublyNode* current = db.start; 
    
    while (current != nullptr) {
        root = insertInTree(root, &(current->content));
        current = current->next;
    }
}

void Search::searchInTree(SearchTreeNode* node, const std::string& prefix, std::vector<Content*>& results, int limit) {
    if (node == nullptr || results.size() >= limit) return;

    std::string currentTitle = toLower(node->content->getTitle());
    std::string searchPrefix = toLower(prefix);

    if (currentTitle.substr(0, searchPrefix.size()) > searchPrefix) {
        searchInTree(node->left, prefix, results, limit);
    }
    else if (matchesPrefix(node->content->getTitle(), prefix)) {
        searchInTree(node->left, prefix, results, limit);

        if (results.size() < limit) {
            results.push_back(node->content);
        }

        searchInTree(node->right, prefix, results, limit);
    }
    else {
        searchInTree(node->right, prefix, results, limit);
    }
}

void Search::autoComplete(const std::string& prefix) {
    if (root == nullptr) {
        std::cout << "Nada foi encontrado.\n";
        return;
    }

    if (prefix.empty()) {
        std::cout << "Digite algo para buscar.\n";
        return;
    }

    std::vector<Content*> results;
    searchInTree(root, prefix, results, 5); 

    std::cout << "\nSugestões para \"" << prefix << "\":\n";
    std::cout << "  ──────────────────────────────────────────────────\n";
    for (auto* content : results) {
        std::cout << " " << content->getTitle() 
                  << " \033[33m(" << content->genreToString(content->getGenre()) << ")\033[0m\n";
    }

    if (results.empty()) {
        std::cout << "Nenhuma sugestão encontrada.\n";
    }
    std::cout << "  ──────────────────────────────────────────────────\n\n";
}
