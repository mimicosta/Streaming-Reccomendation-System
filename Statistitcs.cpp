#include "Statistics.hpp"
#include <iostream>

#define N_TYPES 9
#define N_GENRES 11

ContentType Statistics::typeMostRecommended(ContentDatabase& db){
    ContentType mostRecommended = ContentType::Movie;
    int highest = -1;

    for(int i = 0; i < N_TYPES; i++){
        ContentType currentType = static_cast<ContentType>(i); //converting enum.....
        int current = db.getTypeCount(currentType);
        if(current > highest){
            highest = current;
            mostRecommended = currentType;
        } 
    }
    return mostRecommended;
}

Genre Statistics::genreMostRecommended(ContentDatabase& db){
    Genre mostRecommended = Genre::Action;
    int highest = -1;

    for(int i = 0; i < N_GENRES; i++){
        Genre currentGenre = static_cast<Genre>(i); //converting enum.....
        int current = db.getGenreCount(currentGenre);
        if(current > highest){
            highest = current;
            mostRecommended = currentGenre;
        } 
    }
    return mostRecommended;
}

ContentType Statistics::typeLeastRecommended(ContentDatabase& db){
    ContentType leastRecommended = ContentType::Movie;
    int lowest = 67676767;

    for(int i = 0; i < N_TYPES; i++){
        ContentType currentType = static_cast<ContentType>(i); //converting enum.....
        int current = db.getTypeCount(currentType);
        if(current < lowest){
            lowest = current;
            leastRecommended = currentType;
        } 
    }
    return leastRecommended;
}

Genre Statistics::genreLeastRecommended(ContentDatabase& db){
    Genre leastRecommended = Genre::Action;
    int lowest = 67676767;

    for(int i = 0; i < N_GENRES; i++){
        Genre currentGenre = static_cast<Genre>(i); //converting enum.....
        int current = db.getGenreCount(currentGenre);
        if(current < lowest){
            lowest = current;
            leastRecommended = currentGenre;
        } 
    }
    return leastRecommended;
}

SimpleList Statistics::mostWatchedPerType(ContentDatabase& db, ContentType type){
    SimpleList list;
    DoublyNode* current = db.getStart();
    int highestViews = -1;
    std::string bestTitle = "";

    while(current != nullptr){
        if(current->content.getType() == type){
            if(current->content.getViewCount() > highestViews){
                highestViews = current->content.getViewCount();
                bestTitle = current->content.getTitle();
            }
        }
        current = current->next;
    }
    
    if(highestViews > 0 && !bestTitle.empty()){
        list.add(bestTitle + " (" + std::to_string(highestViews) + " views)");
    }
    return list;
}

SimpleList Statistics::mostWatchedPerGenre(ContentDatabase& db, Genre genre){
    SimpleList list;
    DoublyNode* current = db.getStart();
    int highestViews = -1;
    std::string bestTitle = "";

    while(current != nullptr){
        if(current->content.getGenre() == genre){
            if(current->content.getViewCount() > highestViews){
                highestViews = current->content.getViewCount();
                bestTitle = current->content.getTitle();
            }
        }
        current = current->next;
    }
    
    if(highestViews > 0 && !bestTitle.empty()){
        list.add(bestTitle + " (" + std::to_string(highestViews) + " views)");
    }
    return list;
}

SimpleList Statistics::neverWatchedTitles(ContentDatabase& db){
    SimpleList list;
    DoublyNode* current = db.getStart();

    while(current != nullptr){
        if(current->content.getViewCount() == 0){
            list.add(current->content.getTitle());
        }
        current = current->next;
    }
    return list;
}

int Statistics::allTimeRecomendations(ContentDatabase& db){
    int total = 0;
    for(int i = 0; i < N_TYPES; i++){
        total += db.getTypeCount(static_cast<ContentType>(i)); //converting enum.....
    }
    return total;
}

int Statistics::allTimeVisualizations(ContentDatabase& db){
    int total = 0;
    DoublyNode* current = db.getStart();
    while(current != nullptr){
        total += current->content.getViewCount();
        current = current->next;
    }
    return total;
}