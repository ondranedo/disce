#ifndef OOP_DATABASE_FILM_H
#define OOP_DATABASE_FILM_H

#include <optional>
#include <string_view>
#include <string>

class Film {
public:
    // Rating defaults to std::nullopt, which means its net yet rated by the user
    Film(std::string_view name, std::string_view director, std::optional<float> rating = std::nullopt);
    Film(std::string_view csvRecord);

    [[nodiscard]] std::string name() const;
    [[nodiscard]] std::string director() const;
    // Returns std::nullopt if the film is not rated yet
    [[nodiscard]] std::optional<float> rating() const;

    // Sets the rating of the film
    void setRating(float rating);
    void setName(std::string_view name);
    void setDirector(std::string_view director);

    [[nodiscard]] std::string toString() const;
    [[nodiscard]] std::string toCsvRecord() const;

private:
    std::string m_name;
    std::string m_director;
    std::optional<float>  m_rating;//0 lowest rating, 10 highest rating, std::nullopt not rated yet
};

std::ostream& operator<<(std::ostream& os, const Film& film);

#endif //OOP_DATABASE_FILM_H