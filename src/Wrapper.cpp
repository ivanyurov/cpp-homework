#include "../include/Wrapper.hpp"

std::any Wrapper::execute(const std::unordered_map<std::string, std::any> &args)
{
    if (!caller)
    {
        throw std::runtime_error("No function bound");
    }
    return caller(args);
}