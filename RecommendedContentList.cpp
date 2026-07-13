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
            << "  \033[36m\033[1m🎬 " << current->content.getTitle() << "\033[0m\n"
            << "     \033[33mID:\033[0m " << current->content.getId() << "\n"
            << "     \033[33mTipo:\033[0m " << current->content.typeToString(current->content.getType()) << "\n"
            << "     \033[33mGênero:\033[0m " << current->content.genreToString(current->content.getGenre()) << "\n"
            << "     \033[33mAno:\033[0m " << current->content.getReleaseYear() << " | \033[33mDuração:\033[0m " << current->content.getDuration() << " min\n"
            << "     \033[33mVisualizações:\033[0m " << current->content.getViewCount() << "\n"
            << "     \033[35mDescrição:\033[0m " << current->content.getDescription() << "\n"
            << "  \033[35m──────────────────────────────────────────────────\033[0m\n\n";
        current = current->next;
    }
}

bool RecommendedContentList::correspondsToFilter(const Content& content, const std::string& category) const {
    // 1. Content Type Filter
    if (category.find("Série") != std::string::npos) {
        if (content.getType() != ContentType::Series) return false;
    } else if (category.find("Anime") != std::string::npos) {
        if (content.getType() != ContentType::Anime) return false;
    } else if (category.find("Documentário") != std::string::npos) {
        if (content.getType() != ContentType::Documentary) return false;
    } else if (category.find("Filme") != std::string::npos) {
        if (content.getType() != ContentType::Movie) return false;
    }

    // 2. Release Year Filter
    if (category.find("Clássico") != std::string::npos || category.find("Clássica") != std::string::npos) {
        if (content.getReleaseYear() >= 2015) return false;
    } else if (category.find("Recente") != std::string::npos) {
        if (content.getReleaseYear() < 2015) return false;
    }

    // 3. genre Filter
    Genre genre = content.getGenre();
    if (category.find("Fantasia") != std::string::npos || category.find("Ficção Científica") != std::string::npos || category.find("Sci-Fi") != std::string::npos) {
        if (genre != Genre::Fantasy && genre != Genre::ScienceFiction && genre != Genre::Action) return false;
    } else if (category.find("Comédia") != std::string::npos && category.find("Drama") != std::string::npos) {
        if (genre != Genre::Comedy && genre != Genre::Drama && genre != Genre::Romance) return false;
    } else if (category.find("Comédia") != std::string::npos) {
        if (genre != Genre::Comedy) return false;
    } else if (category.find("Drama") != std::string::npos || category.find("Romance") != std::string::npos) {
        if (genre != Genre::Drama && genre != Genre::Romance) return false;
    } else if (category.find("Crime") != std::string::npos || category.find("Mistério") != std::string::npos || category.find("Suspense") != std::string::npos) {
        if (genre != Genre::Crime && genre != Genre::Mystery && genre != Genre::Thriller && genre != Genre::Horror) return false;
    } else if (category.find("Ação") != std::string::npos || category.find("Aventura") != std::string::npos) {
        if (genre != Genre::Action) return false;
    } else if (category.find("Terror") != std::string::npos) {
        if (genre != Genre::Horror) return false;
    } else if (category.find("Tecnologia") != std::string::npos || category.find("Espaço") != std::string::npos) {
        if (genre != Genre::ScienceFiction) return false;
    }

    return true;
}

RecommendedContentList RecommendedContentList::filterPerCategory(const std::string& category) const {
    RecommendedContentList filteredList;
    DoublyNode* current = head;
    while (current != nullptr) {
        if (correspondsToFilter(current->content, category)) {
            filteredList.addContent(current->content);
        }
        current = current->next;
    }
    return filteredList;
}
