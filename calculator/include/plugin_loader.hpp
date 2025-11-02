#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include "plugin_api.h"
#include <windows.h>

struct LoadedPlugin
{
    std::string name;
    FunctionDescriptor desc;
    HMODULE handle;
};

class PluginManager
{
public:
    bool LoadAll(const std::string &directory);
    const std::vector<LoadedPlugin> &GetFunctions() const { return plugins; }
    void UnloadAll();

private:
    std::vector<LoadedPlugin> plugins;
};
