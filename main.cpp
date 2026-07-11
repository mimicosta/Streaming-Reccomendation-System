#include "ContentDatabase.hpp"
#include "BehaviorTree.hpp"
#include "MostWatchedContentHistory.hpp"
#include "RecommendedContentList.hpp"
#include <string>
#include <iostream>

std::string contentsPath = "setupFiles/contents.txt";
std::string questionsPath = "setupFiles/questions.txt";

void manageCatalog(ContentDatabase& db);
void processRecommendation(ContentDatabase& db, BehaviorTree& tree, MostWatchedContentHistory& history);

int main() {
    ContentDatabase db;
    BehaviorTree tree;
    MostWatchedContentHistory history;

    int opçao = 0;

    while(true){
        std::cout << "\n==============================================\n";
        std::cout << "          🍿 N O D O F L I X 🍿               \n";
        std::cout << "==============================================\n";
        std::cout << "  [1] 📁 Catálogo (listar, inserir ou remover)\n";
        std::cout << "  [2] 🎬 Recomendação personalizada\n";
        std::cout << "  [3] ⏳ Histórico de mais assistidos\n";
        std::cout << "  [4] 📊 Estatísticas gerais do sistema\n";
        std::cout << "  [5] ❌ Sair\n";
        std::cout << "==============================================\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opçao;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\n[!] Entrada inválida. Por favor, digite um número.\n";
            continue;
        }

        switch(opçao) {
            case 1:
                manageCatalog(db);
                break;
            case 2:
                processRecommendation(db, tree, history);
                break;
            case 3:
                history.displayHistory();
                break;
            case 4:
                std::cout << "\nSaindo... Agradecemos por usar a plataforma!\n";
                return 0;
                break;
            default:
                std::cout << "\n[!] Opção inválida. Por favor, escolha uma opção válida! \n";
                break;
        }
    }
}


void manageCatalog(ContentDatabase& db){
    int opçao = 0;
    while (true) {
        std::cout << "\n--- Gerenciamento do catálogo ---\n";
        std::cout << "  [1] Listar conteúdo\n";
        std::cout << "  [2] Inserir conteúdo\n";
        std::cout << "  [3] Remover conteúdo\n";
        std::cout << "  [4] Voltar\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opçao;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\n[!] Entrada inválida. Por favor, digite um número.\n";
            continue;
        }

        if (opçao == 4) {
            break;
        }

        switch(opçao) {
            case 1:
                std::cout << "\n--- LISTA DE CONTEÚDOS ---" << std::endl;
                db.printAll();
                break;
            case 2: {
                int id, duration, releaseYear;
                std::string title, description, typeStr, genreStr;

                std::cout << "Digite o ID do conteúdo: ";
                std::cin >> id;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "[!] ID inválido.\n";
                    break;
                }
                std::cin.ignore(10000, '\n');

                std::cout << "Digite o Titulo: ";
                std::getline(std::cin, title);

                std::cout << "Digite a Descricao: ";
                std::getline(std::cin, description);

                std::cout << "Digite o tipo (Movie, Series, Documentary, Anime, Miniseries, Short Film, Reality Show, TV Program, Show): ";
                std::getline(std::cin, typeStr);

                std::cout << "Digite o gênero (Action, Comedy, Drama, Horror, Science Fiction, Romance, Thriller, Fantasy, Mystery, Crime, Animation): ";
                std::getline(std::cin, genreStr);

                std::cout << "Digite a duração (em minutos): ";
                std::cin >> duration;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "[!] Duração inválida.\n";
                    break;
                }

                std::cout << "Digite o Ano de Lancamento: ";
                std::cin >> releaseYear;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "[!] Ano invalido.\n";
                    break;
                }

                try { // Para tratar essa excessão sem comprometer o funcionamento!
                    ContentType type = Content::stringToType(typeStr);
                    Genre genre = Content::stringToGenre(genreStr);

                    Content* newContent = new Content(id, title, description, type, genre, duration, releaseYear);
                    db.insertContent(newContent);
                    delete newContent;
                    std::cout << "\n[+] Conteudo \"" << title << "\" inserido com sucesso!\n";
                } catch (const std::exception& e) {
                    std::cout << "\n[!] Erro ao inserir conteudo: " << e.what() << "\n";
                }
                break;
            }
            case 3: {
                int id;
                std::cout << "Digite o ID do conteúdo a ser removido: ";
                std::cin >> id;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "[!] ID inválido.\n";
                    break;
                }
                db.removeContent(id);
                std::cout << "\n[-] Remoção concluída do conteúdo com o ID: " << id << "\n";
                break;
            }
            default:
                std::cout << "\n[!] Opção inválida. Por favor, escolha uma opção válida.\n";
                break;
        }
    }
}

void processRecommendation(ContentDatabase& db, BehaviorTree& tree, MostWatchedContentHistory& history) {
    std::cout << "\n--- Recomendacao Personalizada ---" << std::endl;
    std::string category = tree.makeDecision();
    if (category.empty()) {
        std::cout << "[!] Nao foi possivel obter a recomendacao.\n";
        return;
    }

    std::cout << "\n--------------------------------------------\n";
    std::cout << "Categoria Recomendada: " << category << "\n";
    std::cout << "--------------------------------------------\n";

    RecommendedContentList notFilteredList;
    DoublyNode* current = db.getStart();
    while (current != nullptr) {
        notFilteredList.addContent(current->content);
        current = current->next;
    }

    RecommendedContentList filtered = notFilteredList.filterPerCategory(category);

    if (filtered.getHead() == nullptr) {
        std::cout << "Nenhum titulo no catalogo corresponde a essa categoria no momento.\n";
        return;
    }

    std::cout << "Titulos recomendados:\n";
    filtered.display();

    int selectedId = 0;
    std::cout << "\nDigite o ID do conteudo que deseja assistir (ou 0 para cancelar): ";
    std::cin >> selectedId;

    if (std::cin.fail() || selectedId == 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Nenhum conteudo selecionado.\n";
        return;
    }

    DoublyNode* dbCurrent = db.getStart();
    bool found = false;
    while (dbCurrent != nullptr) {
        if (dbCurrent->content.getId() == selectedId) {
            dbCurrent->content.incrementViews();
            
            history.addContent(dbCurrent->content);
            
            std::cout << "\n[!] Assistindo: \"" << dbCurrent->content.getTitle() << "\"...\n";
            std::cout << "Visualização contabilizada com sucesso!\n";
            found = true;
            break;
        }
        dbCurrent = dbCurrent->next;
    }

    if (!found) {
        std::cout << "[!] O ID não foi encontrado nas recomendações.\n";
    }
}

void initializePresets(ContentDatabase& db, BehaviorTree& tree) {
    db.readSetupFile(contentsPath);
    tree.readFile(questionsPath);
}
