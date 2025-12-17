#ifndef ENGINE_H
#define ENGINE_H

#include "Wrapper.hpp"
#include <unordered_map>
#include <string>
#include <stdexcept>

// регистрирует и выполняет команды через обертки
class Engine
{
private:
    std::unordered_map<std::string, Wrapper *> commands;

public:
    // рагистрирует обертку по имени
    void register_command(Wrapper *wrapper, const std::string &name);

    // выполняет команду по имени с аргументами.
    std::any execute(const std::string &name, const std::unordered_map<std::string, std::any> &args);
};

#endif // ENGINE_H