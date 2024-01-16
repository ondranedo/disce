#ifndef OOP_DATABASE_FILMS_H
#define OOP_DATABASE_FILMS_H

#include "Film.h"

#include <vector>

class Films {
public:
    Films();
    Films(const std::initializer_list<Film>& films);

    void addFilm(const Film& film);
    void addFilmSoft(const Film& film) noexcept;
    void removeFilm(const Film& film);

    [[nodiscard]] std::optional<Film> getBestFilm() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] std::string toString() const;

    void orderByRating();

    void saveToFile(std::string_view fileName = "films.csv") const;
    void loadFromFile(std::string_view fileName = "films.csv");

    void replace(std::string_view name, const Film& film);

    [[nodiscard]] std::optional<Film> findFilm(std::string_view name) const;
    [[nodiscard]] std::optional<std::vector<Film>> findFilms(std::string_view name) const;

private:
    std::vector<Film> m_films;
};

std::ostream& operator<<(std::ostream& os, const Films& films);

#endif //OOP_DATABASE_FILMS_H
