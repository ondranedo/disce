#include "Films.h"

#include <ranges>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <fstream>

Films::Films()
: m_films{}{}

Films::Films(const std::initializer_list<Film> &films)
{
    for(const auto& f : films)
        addFilm(f);
}

void Films::addFilm(const Film &film) {
    // Check for duplicates
    for(const auto& f : m_films)
        if(f.name() == film.name() && f.director() == film.director())
            throw std::runtime_error("Film '" + film.name() + "' jiz existuje!");
    m_films.push_back(film);
}

void Films::removeFilm(const Film &removeF) {
    // Find film
    auto it = std::find_if(m_films.begin(), m_films.end(), [&](const Film& film)->bool{
        if(film.name() == removeF.name() && film.director() == removeF.director()) return true;
        return false;
    });
    m_films.erase(it);
}

std::optional<Film> Films::getBestFilm() const {
    if(m_films.empty()) return{};

    return *std::max_element(m_films.begin(), m_films.end(), [](const Film& f1, const Film& f2)->bool{
        if(f1.rating().value_or(-1.0) < f2.rating().value_or(-1.0))
            return true;
        return false;
    });
}

std::string Films::toString() const {
    std::ostringstream ss;

    for(const auto& [i,f ] : m_films | std::views::enumerate)
        ss << '\t' << f.toString() << '\n';

    return ss.str();
}

void Films::orderByRating() {
    std::sort(m_films.begin(), m_films.end(), [](const Film& f1, const Film& f2)->bool{
        if(f1.rating().value_or(-1.0) > f2.rating().value_or(-1.0))
            return true;
        return false;
    });
}

void Films::saveToFile(std::string_view fileName) const {
    std::ofstream out(fileName.data());
    if(!out.is_open())
        throw std::runtime_error("Soubor se nepodarilo otevrit");
    out << "name;director;rating;\n";
    for(const auto& f : m_films)
        out << f.toCsvRecord() << '\n';
    out.close();
}

void Films::loadFromFile(std::string_view fileName) {
    std::ifstream in(fileName.data());
    if(!in.is_open())
        throw std::runtime_error("Soubor se nepodarilo otevrit");
    std::string line;
    std::getline(in, line); // Skip header
    while(std::getline(in, line)){
        addFilmSoft(Film{line});
    }
    in.close();
}

std::optional<Film> Films::findFilm(std::string_view name) const {
    // Find film, try to find it by name, not case sensitive, match first number of characters equal to name length
    size_t count = 0;
    for(const auto& f : m_films) {
        std::string s = f.name().substr(0, name.length());
        if(std::equal(s.begin(), s.end(), name.begin(), name.end(), [](char c1, char c2)->bool{
            return std::tolower(c1) == std::tolower(c2);
        }))
            count++;
    }

    if(count == 0) return {};
    if(count > 1)  throw std::runtime_error("Nalezeno vice filmu, zadejte presnejsi nazev");

    return *std::find_if(m_films.begin(), m_films.end(), [&](const Film& film)->bool{
        std::string s = film.name().substr(0, name.length());
        if(std::equal(s.begin(), s.end(), name.begin(), name.end(), [](char c1, char c2)->bool{
            return std::tolower(c1) == std::tolower(c2);
        }))
            return true;
        return false;
    });
}

size_t Films::size() const {
    return m_films.size();
}

void Films::replace(std::string_view name, const Film &film) {
    auto f = findFilm(name);

    if(!f.has_value())
        throw std::runtime_error("Film '" + std::string(name) + "' nenalezen");

    auto it = std::find_if(m_films.begin(), m_films.end(), [&](const Film& film)->bool{
        if(film.name() == f->name()) return true;
        return false;
    });

    *it = film;
}

std::optional<std::vector<Film>> Films::findFilms(std::string_view name) const {
    std::vector<Film> films;
    for(const auto& f : m_films) {
        std::string s = f.name().substr(0, name.length());
        if(std::equal(s.begin(), s.end(), name.begin(), name.end(), [](char c1, char c2)->bool{
            return std::tolower(c1) == std::tolower(c2);
        }))
            films.push_back(f);
    }

    if(films.empty()) return {};
    return films;
}

void Films::addFilmSoft(const Film &film) noexcept {
    for(const auto& f : m_films)
        if(f.name() == film.name() && f.director() == film.director())
            return;
    m_films.push_back(film);
}

std::ostream &operator<<(std::ostream &os, const Films &films) {
    return os << films.toString();
}
