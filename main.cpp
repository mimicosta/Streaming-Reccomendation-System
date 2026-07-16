#include "ContentDatabase.hpp"
#include "BehaviorTree.hpp"
#include "MostWatchedContentHistory.hpp"
#include "RecommendedContentList.hpp"
#include "Search.hpp"
#include "Statistics.hpp"
#include <string>
#include <iostream>
#include <fstream>

const std::string RESET   = "\033[0m";
const std::string BOLD    = "\033[1m";
const std::string RED     = "\033[31m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[36m";
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
std::string genreRecommendationPath = "setupFiles/genreRecommendation.txt";
std::string typeRecommendationPath = "setupFiles/typeRecommendation.txt";
std::string totalRecommendationsPath = "setupFiles/totalRecommendations.txt";

void manageCatalog(ContentDatabase& db);
void processRecommendation(ContentDatabase& db, BehaviorTree& tree, MostWatchedContentHistory& history, int& totalRecommendations);
void processSearch(ContentDatabase& db, MostWatchedContentHistory& history);
void initializePresets(ContentDatabase& db, BehaviorTree& tree, MostWatchedContentHistory& history);

int main() {
    ContentDatabase db;
    BehaviorTree tree;
    MostWatchedContentHistory history;

    initializePresets(db, tree, history);

    int totalRecommendations = 0;
    {
        std::ifstream inFile(totalRecommendationsPath);
        if (inFile.is_open()) {
            inFile >> totalRecommendations;
        }
    }

    int opçao = 0;

    while(true){
        clearScreen();
        std::cout << MAGENTA << BOLD << "┌──────────────────────────────────────────────┐\n";
        std::cout << "│             🍿  N O D O F L I X  🍿           │\n";
        std::cout << "└──────────────────────────────────────────────┘\n" << RESET;
        std::cout << CYAN << "  [1]" << RESET << " 📁 Catálogo (listar, inserir ou remover)\n";
        std::cout << CYAN << "  [2]" << RESET << " 🎬 Recomendação personalizada\n";
        std::cout << CYAN << "  [3]" << RESET << " ⏳ Histórico de mais assistidos\n";
        std::cout << CYAN << "  [4]" << RESET << " 🔍 Pesquisar por nome\n";
        std::cout << CYAN << "  [5]" << RESET << " 📊 Estatísticas gerais do sistema\n";
        std::cout << CYAN << "  [6]" << RESET << " 👥 Créditos\n";
        std::cout << CYAN << "  [7]" << RESET << " ❌ Sair\n";
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
                processRecommendation(db, tree, history, totalRecommendations);
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
                processSearch(db, history);
                break;
            case 5: {
                clearScreen();
                std::cout << MAGENTA << BOLD << "┌──────────────────────────────────────────────┐\n";
                std::cout << "│         📊 ESTATÍSTICAS GERAIS               │\n";
                std::cout << "└──────────────────────────────────────────────┘\n\n" << RESET;
                
                Statistics stats;
                Content dummy(0, "", "", ContentType::Movie, Genre::Action, 0, 0); // apenas para acessar conversores de Enum para String

                std::cout << CYAN << " • " << RESET << "Tipo mais recomendado: " << BOLD << dummy.typeToString(stats.typeMostRecommended(db)) << RESET << "\n";
                std::cout << CYAN << " • " << RESET << "Tipo menos recomendado: " << BOLD << dummy.typeToString(stats.typeLeastRecommended(db)) << RESET << "\n";
                std::cout << CYAN << " • " << RESET << "Gênero mais recomendado: " << BOLD << dummy.genreToString(stats.genreMostRecommended(db)) << RESET << "\n";
                std::cout << CYAN << " • " << RESET << "Gênero menos recomendado: " << BOLD << dummy.genreToString(stats.genreLeastRecommended(db)) << RESET << "\n";
                std::cout << CYAN << " • " << RESET << "Total de recomendações realizadas: " << BOLD << totalRecommendations << RESET << "\n";
                std::cout << CYAN << " • " << RESET << "Total de visualizações da plataforma: " << BOLD << stats.allTimeVisualizations(db) << RESET << "\n\n";

                std::cout << MAGENTA << "────────────────────────────────────────────────\n" << RESET;
                std::cout << CYAN << BOLD << " 🎬 Mais assistido por Tipo:\n" << RESET;
                for (int i = 0; i < 9; i++) {
                    ContentType t = static_cast<ContentType>(i);
                    SimpleList l = stats.mostWatchedPerType(db, t);
                    if (!l.isEmpty()) {
                        std::cout << "    " << dummy.typeToString(t) << ": " << l.getQuestion(1) << "\n"; // getQuestion começa no index 1
                    }
                }

                std::cout << "\n" << CYAN << BOLD << " 🎭 Mais assistido por Gênero:\n" << RESET;
                for (int i = 0; i < 11; i++) {
                    Genre g = static_cast<Genre>(i);
                    SimpleList l = stats.mostWatchedPerGenre(db, g);
                    if (!l.isEmpty()) {
                        std::cout << "    " << dummy.genreToString(g) << ": " << l.getQuestion(1) << "\n";
                    }
                }

                std::cout << "\n" << CYAN << BOLD << " 👻 Títulos nunca selecionados (0 views):\n" << RESET;
                SimpleList never = stats.neverWatchedTitles(db);
                if (never.isEmpty()) {
                    std::cout << "    Todos os títulos do catálogo já foram assistidos pelo menos uma vez!\n";
                } else {
                    int idx = 1;
                    while (true) {
                        std::string title = never.getQuestion(idx);
                        if (title == "") break;
                        std::cout << "    - " << title << "\n";
                        idx++;
                    }
                }
                std::cout << "\n";
                pauseScreen();
                break;
            }
            case 6:
                clearScreen();
                std::cout << MAGENTA << BOLD << "┌──────────────────────────────────────────────┐\n";
                std::cout << "│                 👥 CRÉDITOS                  │\n";
                std::cout << "└──────────────────────────────────────────────┘\n\n" << RESET;
                std::cout << WHITE << BOLD << "  Desenvolvido por:\n\n" << RESET;
                std::cout << CYAN << "   • Enzo Schubach\n" << RESET;
                std::cout << CYAN << "   • Sofia Macêdo\n" << RESET;
                std::cout << CYAN << "   • Mirella Costa\n\n" << RESET;
                std::cout << MAGENTA << "  ──────────────────────────────────────────────\n\n" << RESET;
                std::cout << WHITE << BOLD << "  Agradecimento Especial:\n\n" << RESET;
                std::cout << WHITE << "  Em agradecimento especial à professora Maria Inês Restovic,\n"
                          << "  por todo o conhecimento compartilhado, pela paciência,\n"
                          << "  dedicação e compreensão ao longo deste semestre.\n\n"
                          << "  Sua orientação foi fundamental para o nosso aprendizado\n"
                          << "  e desenvolvimento desse projeto, cujo nome também foi\n"
                          << "  uma referência ao nosso tão mencionado nodo.\n\n"
                          << "  Nossa sincera gratidão! Nos vemos em ED2 ♥︎\n\n" << RESET;
                std::cout << MAGENTA << "────────────────────────────────────────────────\n" << RESET;
                pauseScreen();
                break;
            case 7:
                db.saveGenreCounts(genreRecommendationPath);
                db.saveTypeCounts(typeRecommendationPath);

                {
                    std::ofstream outFile(totalRecommendationsPath);
                    if (outFile.is_open()) {
                        outFile << totalRecommendations;
                    }
                }
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
                 int id = 1;
                 DoublyNode* currentDb = db.getStart();
                 while (currentDb != nullptr) {
                     if (currentDb->content.getId() >= id) {
                         id = currentDb->content.getId() + 1;
                     }
                     currentDb = currentDb->next;
                 }
                 int duration, releaseYear;
                 std::string title, description, typeStr, genreStr;

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
                     std::cout << GREEN << "\n[+] Conteudo \"" << title << "\" inserido com sucesso com o ID: " << id << "!\n" << RESET;
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

void processRecommendation(ContentDatabase& db, BehaviorTree& tree, MostWatchedContentHistory& history, int& totalRecommendations) {
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

    //increment recommendation
    totalRecommendations++;

    // Incrementa as estatísticas para CADA filme/série que apareceu na lista recomendada
    DoublyNode* recNode = filtered.getHead();
    while (recNode != nullptr) {
        db.incrementGenreCount(recNode->content.getGenre());
        db.incrementTypeCount(recNode->content.getType());
        recNode = recNode->next;
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

void processSearch(ContentDatabase& db, MostWatchedContentHistory& history) {
    Search s;
    s.buildFromDatabase(db);
    std::string prefix;

    while (true) {
        clearScreen();
        std::cout << MAGENTA << BOLD << "┌──────────────────────────────────────────────┐\n";
        std::cout << "│            🔍 PESQUISA DE CONTEÚDO           │\n";
        std::cout << "└──────────────────────────────────────────────┘\n\n" << RESET;
        std::cout << "Digite o nome (ou parte dele) para buscar (ou '0' para voltar): ";
        std::getline(std::cin, prefix);

        if (prefix == "0") {
            break;
        }

        if (prefix.empty()) {
            std::cout << YELLOW << "\nDigite algo para buscar.\n" << RESET;
            pauseScreen();
            continue;
        }

        std::vector<Content*> results = s.search(prefix, 5);

        std::cout << "\nSugestões para \"" << prefix << "\":\n";
        std::cout << "  ──────────────────────────────────────────────────\n";
        if (results.empty()) {
            std::cout << "  Nenhuma sugestão encontrada.\n";
            std::cout << "  ──────────────────────────────────────────────────\n\n";
            std::cout << YELLOW << "Pressione Enter para realizar outra busca..." << RESET;
            std::cin.get();
            continue;
        }

        for (size_t i = 0; i < results.size(); ++i) {
            Content* content = results[i];
            std::cout << "  " << CYAN << "[" << (i + 1) << "]" << RESET << " " << content->getTitle() 
                      << " \033[36m(" << content->genreToString(content->getGenre()) << ")\033[0m\n";
        }
        std::cout << "  ──────────────────────────────────────────────────\n\n";

        int choice = 0;
        std::cout << "Digite o número correspondente para assistir (ou 0 para nova busca): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n');

        if (choice >= 1 && choice <= static_cast<int>(results.size())) {
            Content* selected = results[choice - 1];
            selected->incrementViews();
            
            history.addContent(*selected);
            
            std::cout << GREEN << "\n[!] Assistindo: \"" << selected->getTitle() << "\"...\n" << RESET;
            std::cout << "Visualização contabilizada com sucesso!\n";
            pauseScreen();
        }
    }
}

void initializePresets(ContentDatabase& db, BehaviorTree& tree, MostWatchedContentHistory& history) {
    db.readSetupFile(contentsPath);
    tree.readFile(questionsPath);
    db.loadGenreCounts(genreRecommendationPath);
    db.loadTypeCounts(typeRecommendationPath);

    // Inicializa o historico de mais assistidos a partir das views do banco
    DoublyNode* current = db.getStart();
    while (current != nullptr) {
        if (current->content.getViewCount() > 0) {
            history.addContent(current->content);
        }
        current = current->next;
    }
}
