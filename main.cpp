#include "ContentDatabase.hpp"
#include "BehaviorTree.hpp"
#include <string>
std::string contentsPath = "setupFiles/contents.txt";
std::string questionsPath = "setupFiles/questions.txt";


void initializePresets(){
    ContentDatabase::readSetupFile(questionsPath);
    BehaviorTree::readFile(contentsPath);
}

// int main() {    CÓDIGO QUE A IA GEROU PARA TESTAR FACIL
//     ContentDatabase db;
//     std::string path = "setupFiles/contents.txt";
 
//     std::cout << "Base vazia? " << (db.isEmpty() ? "Sim" : "Nao") << std::endl;
 
//     db.readSetupFile(path);
 
//     std::cout << "Base vazia apos leitura? " << (db.isEmpty() ? "Sim" : "Nao") << std::endl;
//     std::cout << std::endl;
 
//     db.printAll();
 
//     return 0;
// }
 
