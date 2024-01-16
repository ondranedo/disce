#include "Command.h"

#include <sstream>
#include <vector>
#include <string>

#include <ranges>
#include <iomanip>

void Command::execute(const std::vector<std::string> &args)
{
    function(args);
}

std::string Command::name() const {
    return m_name;
}

Command::Command(std::string_view name, std::function<void(const std::vector<std::string> &)> function,
                 std::string_view help)
                 : m_name(name), m_help(help), function(std::move(function))
                 {}

std::string Command::help() const {
    return m_help;
}

void CommandHandler::addCommand(std::string_view commandName, std::function<void(const std::vector<std::string>)> fn, std::string_view help) {
    m_commands.emplace_back(commandName, fn, help);
}

void CommandHandler::executeCommand(const std::string &commandName, const std::vector<std::string> &args) {
    auto it = std::find_if(m_commands.begin(), m_commands.end(), [&](const Command& command)->bool{
        if(command.name() == commandName) return true;
        return false;
    });
    if(it == m_commands.end())
        throw std::runtime_error("Prikaz '" + commandName + "' nenalezen! (Napoveda: help)");
    it->execute(args);
}

std::vector<std::pair<std::string, std::string>> CommandHandler::getHelps() const {
    std::vector<std::pair<std::string, std::string>> helps;
    for(const auto& command : m_commands)
        helps.emplace_back(command.name(), command.help());
    return helps;
}

Console::Console(std::string_view prompt) : m_prompt(prompt) {
    m_commandHandler.addCommand("help", [&](const std::vector<std::string>& args) {
        for(const auto& [commandName, help_msg] : m_commandHandler.getHelps())
                std::cout << '\t' << commandName << "\t - \t" << help_msg << '\n';
    }, "Vypise napovedu");

    m_commandHandler.addCommand("exit", [&](const std::vector<std::string>& args) {
        exit(0);
    }, "Ukonci program");

    m_commandHandler.addCommand("clear", [&](const std::vector<std::string>& args) {
#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
    }, "Vycisti obrazovku");

    m_commandHandler.addCommand("add", [&](const std::vector<std::string>& args) {
        if(args.size() < 2 || args.size() > 3)
            throw std::runtime_error("Nespravne zadane argumenty! (Napoveda: help)");

        if(args.size() == 3)
            m_films.addFilm(Film{args[0], args[1], std::stof(args[2])});
        else
            m_films.addFilm(Film{args[0], args[1], std::nullopt});

    }, "Prida film do databaze: $ add \"<Nazev filmu>\" \"<Reziser>\" [Hodnoceni]");

    m_commandHandler.addCommand("list", [&](const std::vector<std::string>& args) {
        if(m_films.size() == 0)
            throw std::runtime_error("Databaze je prazdna! (Napoveda: help)");

        std::cout << m_films.toString() << '\n';
    }, "Vypise filmy v databazi");

    m_commandHandler.addCommand("save", [&](const std::vector<std::string>& args) {
        if(m_films.size() == 0)
            throw std::runtime_error("Databaze je prazdna! (Napoveda: help)");

        if(args.size() == 1)
            m_films.saveToFile(args[0]);
        else
            m_films.saveToFile();

    }, "Ulozi filmy do souboru: $ save [Nazev souboru]");

    m_commandHandler.addCommand("load", [&](const std::vector<std::string>& args) {
        size_t count = m_films.size();

        if(args.size() == 1)
            m_films.loadFromFile(args[0]);
        else
            m_films.loadFromFile();

        if(m_films.size() == count) return;
        if(m_films.size() - count == 1)
            std::cout << "Nacten " << m_films.size() - count << " film\n";
        if(m_films.size() - count > 1 && m_films.size() - count < 5)
            std::cout << "Nacteny " << m_films.size() - count << " filmy\n";
        if(m_films.size() - count >= 5)
            std::cout << "Nacteno " << m_films.size() - count << " filmu\n";

    }, "Nacte filmy ze souboru: $ load [Nazev souboru]");

    m_commandHandler.addCommand("sort", [&](const std::vector<std::string>& args) {
        if(m_films.size() == 0)
            throw std::runtime_error("Databaze je prazdna! (Napoveda: help)");

        m_films.orderByRating();
    }, "Seradi filmy podle hodnoceni sestupne");

    m_commandHandler.addCommand("delete", [&](const std::vector<std::string>& args) {
        if(m_films.size() == 0)
            throw std::runtime_error("Databaze je prazdna! (Napoveda: help)");

        if(args.size() != 1)
            throw std::runtime_error("Nespravne zadane argumenty! (Napoveda: help)");

        auto film = m_films.findFilm(args[0]);

        if(!film.has_value())
            throw std::runtime_error("Film '" + args[0] + "'... nenalezen! (Napoveda: help)");

        std::cout << "Chcete smazat film '" << film.value().name() << "'? (y/N): ";
        std::string line;
        std::getline(std::cin, line);

        if(line != "y" && line != "Y")
            return;

        m_films.removeFilm(film.value());
    }, "Smaze film z databaze: $ delete \"<Castecny nazev filmu>\"");

    m_commandHandler.addCommand("mark", [&](const std::vector<std::string>& args) {
        if(m_films.size() == 0)
            throw std::runtime_error("Databaze je prazdna! (Napoveda: help)");

        if(args.size() != 2)
            throw std::runtime_error("Nespravne zadane argumenty! (Napoveda: help)");

        auto film = m_films.findFilm(args[0]);
        if(!film.has_value())
            throw std::runtime_error("Film '" + args[0] + "'... nenalezen! (Napoveda: help)");

        film.value().setRating(std::stof(args[1]));
        m_films.replace(args[0], film.value());

    }, "Nastavi hodnoceni filmu: $ mark \"<Castecny nazev filmu>\" <Hodnoceni>");

    m_commandHandler.addCommand("find", [&](const std::vector<std::string>& args) {
        if(m_films.size() == 0)
            throw std::runtime_error("Databaze je prazdna! (Napoveda: help)");

        if(args.size() != 1)
            throw std::runtime_error("Nespravne zadane argumenty! (Napoveda: help)");

        auto film = m_films.findFilms(args[0]);
        if(!film.has_value())
            throw std::runtime_error("Zadne filmy '" + args[0] + "'... nenalezeny! (Napoveda: help)");

        for(const auto& f : film.value())
            std::cout << '\t' << f << '\n';

    }, "Najde filmy v databazi: $ find \"<Castecny nazev filmu>\"");

    m_commandHandler.addCommand("best", [&](const std::vector<std::string>& args) {
        if(m_films.size() == 0)
            throw std::runtime_error("Databaze je prazdna! (Napoveda: help)");

        auto film = m_films.getBestFilm();
        if(!film.has_value())
            throw std::runtime_error("Nenalezeny zadne filmy! (Napoveda: help)");

        std::cout << '\t' << film.value() << '\n';

    }, "Vypise nejlepsi film v databazi");

    m_commandHandler.addCommand("edit", [&](const std::vector<std::string>& args) {
        if(m_films.size() == 0)
            throw std::runtime_error("Databaze je prazdna! (Napoveda: help)");

        if(args.size() != 1)
            throw std::runtime_error("Nespravne zadane argumenty! (Napoveda: help)");

        auto film = m_films.findFilm(args[0]);
        if(!film.has_value())
            throw std::runtime_error("Film '" + args[0] + "'... nenalezen! (Napoveda: help)");

        std::cout << "Puvodni nazev: " << film.value().name() << '\n';
        std::cout << "Zadejte novy nazev filmu: ";
        std::string line;
        std::getline(std::cin, line);
        film.value().setName(line);

        std::cout << "Puvodni reziser: " << film.value().director() << '\n';
        std::cout << "Zadejte noveho rezisera: ";
        std::getline(std::cin, line);
        film.value().setDirector(line);

        std::cout << "Puvodni hodnoceni: ";
        if(film.value().rating().has_value())
            std::cout << film.value().rating().value() << '\n';
        else
            std::cout << "Neni hodnocen\n";

        std::cout << "Zadejte nove hodnoceni (nic => nehodnoceno): ";
        std::getline(std::cin, line);
        if(!line.empty())
            film.value().setRating(std::stof(line));

        m_films.replace(args[0], film.value());

    }, "Upravi film v databazi: $ edit \"<Castecny nazev filmu>\"");
}

void Console::run() {
    while(1)
    {
        // Print prompt
        std::cout << m_prompt << " (" << m_films.size()  << ") $ " << std::flush;
        std::string line;
        std::getline(std::cin, line);
        if(line.empty()) // Skip empty lines (enter)
            continue;
        std::istringstream in(line);
        std::string commandName, tmp_arg;
        in >> commandName;

        std::vector<std::string> args;

        // Read arguments, separated by spaces or quotes
        while(in >> std::quoted(tmp_arg))
            args.push_back(tmp_arg);

        try {
            m_commandHandler.executeCommand(commandName, args);
        } catch (const std::exception& e) {
            std::cout << "Chyba: " << e.what() << '\n';
        }
    }
}
