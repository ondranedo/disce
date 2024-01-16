#ifndef OOP_DATABASE_COMMAND_H
#define OOP_DATABASE_COMMAND_H

#include <iostream>
#include <functional>
#include <vector>
#include "Films.h"

class Command {
public:
    Command(std::string_view name, std::function<void(const std::vector<std::string>& /* args */)> function, std::string_view help);

    void execute(const std::vector<std::string>& args);
    [[nodiscard]] std::string name() const;
    [[nodiscard]] std::string help() const;
private:
    std::string m_name, m_help;
    std::function<void(const std::vector<std::string>& /* args */)> function;
};

class CommandHandler {
public:
    void addCommand(std::string_view commandName, std::function<void(const std::vector<std::string>)> fn, std::string_view help);
    void executeCommand(const std::string& commandName, const std::vector<std::string>& args);

    std::vector<std::pair<std::string, std::string>> getHelps() const;
private:
    std::vector<Command> m_commands;
};

class Console {
public:
    Console(std::string_view prompt);

    void run();

private:
    CommandHandler m_commandHandler;
    std::string m_prompt;
    Films m_films;
};

#endif //OOP_DATABASE_COMMAND_H
