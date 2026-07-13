#include "ContentDatabase.hpp"
#include "BehaviorTree.hpp"
#include "MostWatchedContentHistory.hpp"
#include "RecommendedContentList.hpp"
#include <string>
#include <iostream>

const std::string RESET   = "\033[0m";
const std::string BOLD    = "\033[1m";
const std::string RED     = "\033[31m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string BLUE    = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN    = "\033[36m";
const std::string WHITE   = "\033[37m";

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void pauseScreen() {
    std::cout << YELLOW << "\nPressione Enter para continuar..." << RESET;
    std::cin.get();
}

std::string contentsPath = "setupFiles/contents.txt";
std::string questionsPath = "setupFiles/questions.txt";

void manageCatalog(ContentDatabase& db);
void processRecommendation(ContentDatabase& db, BehaviorTree& tree, MostWatchedContentHistory& history);
void initializePresets(ContentDatabase& db, BehaviorTree& tree);

int main() {
    ContentDatabase db;
    BehaviorTree tree;
    MostWatchedContentHistory history;

    initializePresets(db, tree);

    int opçao = 0;

    while(true){
        clearScreen();
        std::cout << MAGENTA << BOLD << "┌──────────────────────────────────────────────┐\n";
        std::cout << "│             🍿  N O D O F L I X  🍿           │\n";
        std::cout << "└──────────────────────────────────────────────┘\n" << RESET;
        std::cout << CYAN << "  [1]" << RESET << " 📁 Catálogo (listar, inserir ou remover)\n";
        std::cout << CYAN << "  [2]" << RESET << " 🎬 Recomendação personalizada\n";
        std::cout << CYAN << "  [3]" << RESET << " ⏳ Histórico de mais assistidos\n";
        std::cout << CYAN << "  [4]" << RESET << " 📊 Estatísticas gerais do sistema\n";
        std::cout << CYAN << "  [5]" << RESET << " ❌ Sair\n";
        std::cout << MAGENTA << "────────────────────────────────────────────────\n" << RESET;
        std::cout << "Escolha uma opção: ";
        std::cin >> opçao;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << RED << "\n[!] Entrada inválida. Por favor, digite um número.\n" << RESET;
            pauseScreen();
            continue;
        }
        std::cin.ignore(10000, '\n'); 

        switch(opçao) {
            case 1:
                manageCatalog(db);
                break;
            case 2:
                processRecommendation(db, tree, history);
                break;
            case 3:
                clearScreen();
                std::cout << MAGENTA << BOLD << "┌──────────────────────────────────────────────┐\n";
                std::cout << "│        ⏳ HISTÓRICO DE MAIS ASSISTIDOS       │\n";
                std::cout << "└──────────────────────────────────────────────┘\n\n" << RESET;
                history.displayHistory();
                pauseScreen();
                break;
            case 4:
                clearScreen();
                std::cout << MAGENTA << BOLD << "┌──────────────────────────────────────────────┐\n";
                std::cout << "│         📊 ESTATÍSTICAS GERAIS               │\n";
                std::cout << "└──────────────────────────────────────────────┘\n\n" << RESET;
                std::cout << "Recurso em desenvolvimento ou nenhuma estatística disponível.\n";
                pauseScreen();
                break;
            case 5:
                clearScreen();
                std::cout << GREEN << "\nSaindo... Agradecemos por usar a plataforma!\n\n" << RESET;
                return 0;
            default:
                std::cout << RED << "\n[!] Opção inválida. Por favor, escolha uma opção válida!\n" << RESET;
                pauseScreen();
                break;
        }
    }
}

void manageCatalog(ContentDatabase& db){
    int opçao = 0;
    while (true) {
        clearScreen();
        std::cout << MAGENTA << BOLD << "┌──────────────────────────────────────────────┐\n";
        std::cout << "│        📁 GERENCIAMENTO DO CATÁLOGO          │\n";
        std::cout << "└──────────────────────────────────────────────┘\n" << RESET;
        std::cout << CYAN << "  [1]" << RESET << " Listar conteúdo\n";
        std::cout << CYAN << "  [2]" << RESET << " Inserir conteúdo\n";
        std::cout << CYAN << "  [3]" << RESET << " Remover conteúdo\n";
        std::cout << CYAN << "  [4]" << RESET << " Voltar ao menu principal\n";
        std::cout << MAGENTA << "────────────────────────────────────────────────\n" << RESET;
        std::cout << "Escolha uma opção: ";
        std::cin >> opçao;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << RED << "\n[!] Entrada inválida. Por favor, digite um número.\n" << RESET;
            pauseScreen();
            continue;
        }
        std::cin.ignore(10000, '\n');

        if (opçao == 4) {
            break;
        }

        switch(opçao) {
            case 1:
                clearScreen();
                std::cout << BLUE << BOLD << "┌──────────────────────────────────────────────┐\n";
                std::cout << "│             LISTA DE CONTEÚDOS               │\n";
                std::cout << "└──────────────────────────────────────────────┘\n\n" << RESET;
                db.printAll();
                pauseScreen();
                break;
            case 2: {
                clearScreen();
                std::cout << BLUE << BOLD << "┌──────────────────────────────────────────────┐\n";
                std::cout << "│              INSERIR CONTEÚDO                │\n";
                std::cout << "└──────────────────────────────────────────────┘\n\n" << RESET;
                int id, duration, releaseYear;
                std::string title, description, typeStr, genreStr;

                std::cout << "Digite o ID do conteúdo: ";
                std::cin >> id;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << RED << "[!] ID inválido.\n" << RESET;
                    pauseScreen();
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
                    std::cout << RED << "[!] Duração inválida.\n" << RESET;
                    pauseScreen();
                    break;
                }
                std::cin.ignore(10000, '\n');

                std::cout << "Digite o Ano de Lancamento: ";
                std::cin >> releaseYear;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << RED << "[!] Ano invalido.\n" << RESET;
                    pauseScreen();
                    break;
                }
                std::cin.ignore(10000, '\n');

                try { 
                    ContentType type = Content::stringToType(typeStr);
                    Genre genre = Content::stringToGenre(genreStr);

                    Content* newContent = new Content(id, title, description, type, genre, duration, releaseYear);
                    db.insertContent(newContent);
                    delete newContent;
                    std::cout << GREEN << "\n[+] Conteudo \"" << title << "\" inserido com sucesso!\n" << RESET;
                } catch (const std::exception& e) {
                    std::cout << RED << "\n[!] Erro ao inserir conteudo: " << e.what() << "\n" << RESET;
                }
                pauseScreen();
                break;
            }
            case 3: {
                clearScreen();
                std::cout << BLUE << BOLD << "┌──────────────────────────────────────────────┐\n";
                std::cout << "│              REMOVER CONTEÚDO                │\n";
                std::cout << "└──────────────────────────────────────────────┘\n\n" << RESET;
                int id;
                std::cout << "Digite o ID do conteúdo a ser removido: ";
                std::cin >> id;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << RED << "[!] ID inválido.\n" << RESET;
                    pauseScreen();
                    break;
                }
                std::cin.ignore(10000, '\n');
                db.removeContent(id);
                std::cout << GREEN << "\n[-] Remoção concluída do conteúdo com o ID: " << id << "\n" << RESET;
                pauseScreen();
                break;
            }
            default:
                std::cout << RED << "\n[!] Opção inválida. Por favor, escolha uma opção válida.\n" << RESET;
                pauseScreen();
                break;
        }
    }
}

void processRecommendation(ContentDatabase& db, BehaviorTree& tree, MostWatchedContentHistory& history) {
    clearScreen();
    std::cout << MAGENTA << BOLD << "┌──────────────────────────────────────────────┐\n";
    std::cout << "│          🎬 RECOMENDAÇÃO PERSONALIZADA        │\n";
    std::cout << "└──────────────────────────────────────────────┘\n\n" << RESET;

    std::cout << CYAN << BOLD << "  =================== INSTRUÇÕES ===================\n" << RESET;
    std::cout << WHITE << BOLD << "  Para responder às perguntas do sistema, utilize:\n" << RESET;
    std::cout << "    ➦ " << GREEN << BOLD << "1" << RESET << " para " << GREEN << BOLD << "SIM\n" << RESET;
    std::cout << "    ➦ " << RED << BOLD << "0" << RESET << " para " << RED << BOLD << "NÃO\n" << RESET;
    std::cout << CYAN << BOLD << "  ==================================================\n\n" << RESET;

    std::cout << YELLOW << "Pressione Enter para começar o questionário..." << RESET;
    std::cin.get();

    std::string category = tree.makeDecision();
    if (category.empty()) {
        std::cout << RED << "[!] Nao foi possivel obter a recomendacao.\n" << RESET;
        pauseScreen();
        return;
    }

    clearScreen();
    std::cout << MAGENTA << BOLD << "┌──────────────────────────────────────────────┐\n";
    std::cout << "│          🎬 RECOMENDAÇÃO PERSONALIZADA        │\n";
    std::cout << "└──────────────────────────────────────────────┘\n\n" << RESET;

    std::cout << GREEN << BOLD << "  =================== RESULTADO ===================\n" << RESET;
    std::cout << WHITE << BOLD << "  Categoria recomendada: " << category << "\n";
    std::cout << GREEN << BOLD << "  =================================================\n\n" << RESET;

    RecommendedContentList notFilteredList;
    DoublyNode* current = db.getStart();
    while (current != nullptr) {
        notFilteredList.addContent(current->content);
        current = current->next;
    }

    RecommendedContentList filtered = notFilteredList.filterPerCategory(category);

    if (filtered.getHead() == nullptr) {
        std::cout << YELLOW << "Nenhum titulo no catalogo corresponde a essa categoria no momento.\n" << RESET;
        pauseScreen();
        return;
    }

    std::cout << CYAN << BOLD << "  🎬 TÍTULOS RECOMENDADOS DISPONÍVEIS:\n";
    std::cout << "  ──────────────────────────────────────────────────\n\n" << RESET;
    filtered.display();

    int selectedId = 0;
    std::cout << "Digite o ID do conteudo que deseja assistir (ou 0 para cancelar): ";
    std::cin >> selectedId;

    if (std::cin.fail() || selectedId == 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << YELLOW << "\nNenhum conteudo selecionado.\n" << RESET;
        pauseScreen();
        return;
    }
    std::cin.ignore(10000, '\n');

    DoublyNode* dbCurrent = db.getStart();
    bool found = false;
    while (dbCurrent != nullptr) {
        if (dbCurrent->content.getId() == selectedId) {
            dbCurrent->content.incrementViews();
            
            history.addContent(dbCurrent->content);
            
            std::cout << GREEN << "\n[!] Assistindo: \"" << dbCurrent->content.getTitle() << "\"...\n" << RESET;
            std::cout << "Visualização contabilizada com sucesso!\n";
            found = true;
            break;
        }
        dbCurrent = dbCurrent->next;
    }

    if (!found) {
        std::cout << RED << "[!] O ID não foi encontrado nas recomendações.\n" << RESET;
    }
    pauseScreen();
}

void initializePresets(ContentDatabase& db, BehaviorTree& tree) {
    db.readSetupFile(contentsPath);
    tree.readFile(questionsPath);
}
