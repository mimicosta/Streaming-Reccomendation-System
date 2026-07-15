#pragma once

#include <string>
#include <stdexcept>

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
    Content(
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
          viewCount((id % 5 == 0) ? 0 : ((id * 113) % 9999 + 1)), 
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

    static Genre stringToGenre(const std::string& str) {
        if (str == "Action") return Genre::Action;
        if (str == "Comedy") return Genre::Comedy;
        if (str == "Drama") return Genre::Drama;
        if (str == "Horror") return Genre::Horror;
        if (str == "Science Fiction") return Genre::ScienceFiction;
        if (str == "Romance") return Genre::Romance;
        if (str == "Thriller") return Genre::Thriller;
        if (str == "Fantasy") return Genre::Fantasy;
        if (str == "Mystery") return Genre::Mystery;
        if (str == "Crime") return Genre::Crime;
        if (str == "Animation") return Genre::Animation;
        throw std::invalid_argument("Genero invalido: " + str);
    }

    static ContentType stringToType(const std::string& str) {
        if (str == "Movie") return ContentType::Movie;
        if (str == "Series") return ContentType::Series;
        if (str == "Documentary") return ContentType::Documentary;
        if (str == "Anime") return ContentType::Anime;
        if (str == "Miniseries") return ContentType::Miniseries;
        if (str == "Short Film") return ContentType::ShortFilm;
        if (str == "Reality Show") return ContentType::RealityShow;
        if (str == "TV Program") return ContentType::TVProgram;
        if (str == "Show") return ContentType::Show;
        throw std::invalid_argument("Genero invalido: " + str);
    }
};