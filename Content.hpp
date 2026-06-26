#pragma once

#include <string>

enum class Genre { //Available Genres
    Action,
    Comedy,
    Drama,
    Horror,
    ScienceFiction,
    Romance,
    Thriller,
    Fantasy,
    Mystery,
    Crime,
    Animation
};

enum class ContentType { //Available Contents
    Movie,
    Series,
    Documentary,
    Anime,
    Miniseries,
    ShortFilm,
    RealityShow,
    TVProgram,
    Show
};

class Content { //Content Atributes
private:
    int id;
    std::string title;
    std::string description;
    ContentType type;
    Genre genre;
    int duration;
    int viewCount;
    int releaseYear;

public:
    Content( //Constructor
        int id,
        const std::string& title,
        const std::string& description,
        ContentType type,
        Genre genre,
        int duration,
        int releaseYear
    )
        : id(id),
          title(title),
          description(description),
          type(type),
          genre(genre),
          duration(duration),
          viewCount(0),
          releaseYear(releaseYear) {}

    //Getters      
    int getId() const { return id; }
    const std::string& getTitle() const { return title; }
    const std::string& getDescription() const { return description; }
    ContentType getType() const { return type; }
    Genre getGenre() const { return genre; }
    int getDuration() const { return duration; }
    int getViewCount() const { return viewCount; }
    int getReleaseYear() const { return releaseYear; }

    void incrementViews() {
        viewCount++;
    }

    std::string genreToString(Genre genre) {
    switch (genre) {
        case Genre::Action: return "Action";
        case Genre::Comedy: return "Comedy";
        case Genre::Drama: return "Drama";
        case Genre::Horror: return "Horror";
        case Genre::ScienceFiction: return "Science Fiction";
        case Genre::Romance: return "Romance";
        case Genre::Thriller: return "Thriller";
        case Genre::Fantasy: return "Fantasy";
        case Genre::Mystery: return "Mystery";
        case Genre::Crime: return "Crime";
        case Genre::Animation: return "Animation";
    }
    return "";
    }

    std::string typeToString(ContentType type) {
    switch (type) {
        case ContentType::Movie: return "Movie";
        case ContentType::Series: return "Series";
        case ContentType::Documentary: return "Documentary";
        case ContentType::Anime: return "Anime";
        case ContentType::Miniseries: return "Miniseries";
        case ContentType::ShortFilm: return "Short Film";
        case ContentType::RealityShow: return "Reality Show";
        case ContentType::TVProgram: return "TV Program";
        case ContentType::Show: return "Show";
    }
    return "";
    }   
};