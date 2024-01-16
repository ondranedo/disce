#include "Film.h"

#include <string_view>
#include <stdexcept>
#include <sstream>

Film::Film(std::string_view name, std::string_view director, std::optional<float> rating)
: m_name(name), m_director(director), m_rating(rating) {
    if(m_name.empty())
        throw std::runtime_error("Jmeno musi byt vyplneno");
    if(m_director.empty())
        throw std::runtime_error("Reziser musi byt vyplnen");
    if(m_rating.has_value() && (m_rating.value() < 0 || m_rating.value() > 10))
        throw std::runtime_error("Hodnoceni musi byt mezi 0.0 a 10.0");
}

std::string Film::name() const {
    return m_name;
}

std::string Film::director() const {
    return m_director;
}

std::optional<float> Film::rating() const {
    if(m_rating.has_value() && (m_rating.value() < 0 || m_rating.value() > 10))
        throw std::runtime_error("Rating must be between 0 and 10");
    return m_rating;
}

void Film::setRating(float rating) {
    if(rating < 0 || rating > 10)
        throw std::runtime_error("Hodnoceni musi byt mezi 0.0 a 10.0");
    else
        m_rating.emplace(rating);
}

std::string Film::toString() const {
    std::ostringstream out;
    out.precision(1);
    out << m_name << " (" << m_director << ")";
    if(m_rating.has_value())
        out << " " << std::fixed << m_rating.value();
    return out.str();
}

std::string Film::toCsvRecord() const {
    std::ostringstream out;
    out.precision(1);
    out << m_name << ";" << m_director << ';';
    if(m_rating.has_value())
        out << std::fixed << m_rating.value();
    out << ';';

    return out.str();
}

Film::Film(std::string_view csvRecord) {
    std::istringstream in(csvRecord.data());
    std::string name, director, rating;
    std::getline(in, name, ';');
    std::getline(in, director, ';');
    std::getline(in, rating, ';');

    m_name = name;
    m_director = director;
    if(rating.empty())
        m_rating = std::nullopt;
    else
        m_rating = std::stof(rating);
}

void Film::setName(std::string_view name) {
    m_name = name;
}

void Film::setDirector(std::string_view director) {
    m_director = director;
}

std::ostream &operator<<(std::ostream &os, const Film &film) {
    os << film.toString();
    return os;
}
