#include "RecommendedContentList.hpp"
#include <iostream>

void RecommendedContentList::addContent(const Content& content) {
    DoublyNode * newNode = new DoublyNode(content);
    if (!head) {
        head = newNode;
        return;
    } 
    if (content.getTitle() < head->content.getTitle()) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    DoublyNode * current = head;
    while (current->next && current->next->content.getTitle() < content.getTitle()) {
        current = current->next;
    }
    
    newNode->next = current->next;
    if (current->next) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
}

void RecommendedContentList::removeContent(int id) {
    if(!head) return;

    if(head->content.getId() == id) {
        DoublyNode* temp = head;
        head = head->next;
        if(head) head->prev = nullptr;
        delete temp;
        return;
    }
    
    DoublyNode* current = head;
    while(current && current->content.getId() != id) {
        current = current->next;
    }

    if(current) {
        if(current->prev) {
            current->prev->next = current->next;
        }
        if(current->next) {
            current->next->prev = current->prev;
        }
        delete current;
    }
}

void RecommendedContentList::display() const {
    DoublyNode* current = head;

    while (current) {
        std::cout
            << "Title: " << current->content.getTitle()
            << "\n Type: " << current->content.typeToString(current->content.getType())
            << "\n Genre: " << current->content.genreToString(current->content.getGenre())
            << "\n Release Year: " << current->content.getReleaseYear()
            << "\n Views: " << current->content.getViewCount()
            << "\n\n";
        current = current->next;
    }
}