#include "../include/Engine.hpp"

void Engine::register_command(Wrapper *wrapper, const std::string &name)
{
    if (commands.find(name) != commands.end())
    {
        throw std::invalid_argument("Command already registered: " + name);
    }
    commands[name] = wrapper;
}

std::any Engine::execute(const std::string &name, const std::unordered_map<std::string, std::any> &args)
{
    auto it = commands.find(name);
    if (it == commands.end())
    {
        throw std::invalid_argument("Unknown command: " + name);
    }
    return it->second->execute(args);
}