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

void ContentDatabase::printAll() {
    DoublyNode* current = start;
    int count = 1;
    while (current != nullptr) {
        Content& c = current->content;
        std::cout << "--- Conteudo " << count << " ---" << std::endl;
        std::cout << "ID: " << c.getId() << std::endl;
        std::cout << "Titulo: " << c.getTitle() << std::endl;
        std::cout << "Descricao: " << c.getDescription() << std::endl;
        std::cout << "Tipo: " << c.typeToString(c.getType()) << std::endl;
        std::cout << "Genero: " << c.genreToString(c.getGenre()) << std::endl;
        std::cout << "Duracao: " << c.getDuration() << " min" << std::endl;
        std::cout << "Ano: " << c.getReleaseYear() << std::endl;
        std::cout << std::endl;
        current = current->next;
        count++;
    }
}
