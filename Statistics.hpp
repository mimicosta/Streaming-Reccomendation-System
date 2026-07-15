#pragma once

#include "SimpleList"
#include <string>
#include "ContentDatabase.hpp"
#include "Content.hpp"

class Statistics{
    public:
        typeMostRecommended();
        genreMostRecommended();
        typeLeastRecommended();
        genreLeastRecommended();
        mostWatchedPerType(contentType type);
        mostWatchedPerGenre(Genre genre);
        neverWatchedTitles();
        allTimeRecomendations();
        allTimeVisualizations();
}