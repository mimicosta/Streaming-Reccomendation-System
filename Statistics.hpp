#pragma once

#include "SimpleList.hpp"
#include <string>
#include "ContentDatabase.hpp"
#include "Content.hpp"

class Statistics{
    public:
        ContentType typeMostRecommended(ContentDatabase& db);
        Genre genreMostRecommended(ContentDatabase& db);
        ContentType typeLeastRecommended(ContentDatabase& db);
        Genre genreLeastRecommended(ContentDatabase& db);
        SimpleList mostWatchedPerType(ContentDatabase& db, ContentType type);
        SimpleList mostWatchedPerGenre(ContentDatabase& db, Genre genre);
        SimpleList neverWatchedTitles(ContentDatabase& db);
        int allTimeRecomendations(ContentDatabase& db);
        int allTimeVisualizations(ContentDatabase& db);
};