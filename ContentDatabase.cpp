#include "ContentDatabase.hpp"

ContentDatabase::ContentDatabase() {
    start = nullptr;
}

ContentDatabase::~ContentDatabase() {
    DoublyNode* current = start;
    while (current != nullptr) {
        DoublyNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

bool ContentDatabase::isEmpty(){
    return (start == nullptr);
}

void ContentDatabase::insertContent(Content *newContent){
    DoublyNode *newNode = new DoublyNode(*newContent);

    if(isEmpty()){ start = newNode; return; } 

    DoublyNode *tempNode = start;

    while(tempNode->next != nullptr) tempNode = tempNode->next;
    tempNode->next = newNode;
    newNode->prev = tempNode;

    tempNode = nullptr;
}

void ContentDatabase::readSetupFile(std::string filepath){
    std::ifstream fileContent(filepath);
    std::string currentLine;
    
    int id, duration, releaseYear;
    Genre genre;
    ContentType type;
    std::string title, description;
    
    while(std::getline(fileContent, currentLine)){
        id = std::stoi(currentLine);

        std::getline(fileContent, currentLine);
        title = currentLine;

        std::getline(fileContent, currentLine);
        description = currentLine;

        std::getline(fileContent, currentLine);
        type = Content::stringToType(currentLine);

        std::getline(fileContent, currentLine);
        genre = Content::stringToGenre(currentLine);

        std::getline(fileContent, currentLine);
        duration = std::stoi(currentLine);

        std::getline(fileContent, currentLine);
        releaseYear = std::stoi(currentLine);
    
        Content* newContent = new Content(id, title, description, type, genre, duration, releaseYear);
        ContentDatabase::insertContent(newContent);
        delete newContent;
    }
}

void ContentDatabase::removeContent(int id) {
    if (isEmpty()) return;

    DoublyNode* current = start;

    if (start->content.getId() == id) {
        start = start->next;
        if (start != nullptr) {
            start->prev = nullptr;
        }
        delete current;
        return;
    }

    while (current != nullptr && current->content.getId() != id) {
        current = current->next;
    }

    if (current != nullptr) {
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }
        delete current;
    }
}


void ContentDatabase::printAll() {
    DoublyNode* current = start;
    int count = 1;
    while (current != nullptr) {
        Content& c = current->content;
        std::cout
            << "  \033[36m\033[1m🎬 [" << count << "] " << c.getTitle() << "\033[0m\n"
            << "     \033[33mID:\033[0m " << c.getId() << "\n"
            << "     \033[33mTipo:\033[0m " << c.typeToString(c.getType()) << "\n"
            << "     \033[33mGênero:\033[0m " << c.genreToString(c.getGenre()) << "\n"
            << "     \033[33mAno:\033[0m " << c.getReleaseYear() << " | \033[33mDuração:\033[0m " << c.getDuration() << " min\n"
            << "     \033[35mDescrição:\033[0m " << c.getDescription() << "\n"
            << "  \033[35m──────────────────────────────────────────────────\033[0m\n\n";
        current = current->next;
        count++;
    }
}
