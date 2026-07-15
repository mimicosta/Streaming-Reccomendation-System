#include "MostWatchedContentHistory.hpp"
#include <iostream>

void MostWatchedContentHistory::addContent(const Content& content) {
    // 1. Check if the content is already in the history list
    DoublyNode* current = head;
    DoublyNode* existingNode = nullptr;
    while (current != nullptr) {
        if (current->content.getId() == content.getId()) {
            existingNode = current;
            break;
        }
        current = current->next;
    }

    if (existingNode) {
        existingNode->content = content; 

        if (existingNode == head) {
            return;
        }

        if (existingNode->prev) {
            existingNode->prev->next = existingNode->next;
        }
        if (existingNode->next) {
            existingNode->next->prev = existingNode->prev;
        } else {
            tail = existingNode->prev;
        }

        existingNode->next = nullptr;
        existingNode->prev = nullptr;

        DoublyNode* target = head;
        if (existingNode->content.getViewCount() > target->content.getViewCount()) {
            existingNode->next = target;
            target->prev = existingNode;
            head = existingNode;
            return;
        }

        while (target->next && target->next->content.getViewCount() >= existingNode->content.getViewCount()) {
            target = target->next;
        }

        existingNode->next = target->next;
        existingNode->prev = target;
        if (target->next) {
            target->next->prev = existingNode;
        } else {
            tail = existingNode;
        }
        target->next = existingNode;

    } else {
        DoublyNode* newNode = new DoublyNode(content);

        if (!head) {
            head = newNode;
            tail = newNode;
            return;
        }

        if (newNode->content.getViewCount() > head->content.getViewCount()) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        }

        DoublyNode* target = head;
        while (target->next && target->next->content.getViewCount() >= newNode->content.getViewCount()) {
            target = target->next;
        }

        newNode->next = target->next;
        newNode->prev = target;
        if (target->next) {
            target->next->prev = newNode;
        } else {
            tail = newNode;
        }
        target->next = newNode;
    }
}

void MostWatchedContentHistory::displayHistory() const {
    if (head == nullptr) {
        std::cout << "   \033[36mNenhum histórico de visualização disponível ainda.\033[0m\n";
        return;
    }
    DoublyNode* current = head;
    int rank = 1;
    while (current) {
        std::string medal = "  ";
        if (rank == 1) medal = "🏆 ";
        else if (rank == 2) medal = "🥈 ";
        else if (rank == 3) medal = "🥉 ";

        std::cout
            << "  " << medal << "\033[36m\033[1mRank #" << rank << " - " << current->content.getTitle() << "\033[0m\n"
            << "     \033[36mTipo:\033[0m " << current->content.typeToString(current->content.getType())
            << " | \033[36mGênero:\033[0m " << current->content.genreToString(current->content.getGenre())
            << " | \033[32mVisualizações:\033[0m " << current->content.getViewCount() << "\n"
            << "  \033[35m──────────────────────────────────────────────────\033[0m\n\n";
        current = current->next;
        rank++;
    }
}