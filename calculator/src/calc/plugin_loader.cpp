#include "plugin_loader.hpp"

bool PluginManager::LoadAll(const std::string &directory)
{
    plugins.clear();

    if (!std::filesystem::exists(directory))
    {
        std::cout << "Plugins directory not found: " << directory << "\n";
        return false;
    }

    for (const auto &entry : std::filesystem::directory_iterator(directory))
    {
        if (!entry.is_regular_file())
            continue;

        auto path = entry.path();
        if (path.extension() != ".dll")
            continue;

        HMODULE handle = LoadLibraryA(path.string().c_str());
        if (!handle)
        {
            std::cout << "Failed to load plugin: " << path.filename().string() << "\n";
            continue;
        }

        auto func = (FunctionDescriptor (*)())GetProcAddress(handle, "GetFunctionDescriptor");
        if (!func)
        {
            std::cout << "Invalid plugin (no GetFunctionDescriptor): " << path.filename().string() << "\n";
            FreeLibrary(handle);
            continue;
        }

        FunctionDescriptor desc = func();
        if (!desc.name || !desc.ptr)
        {
            std::cout << "Invalid descriptor in " << path.filename().string() << "\n";
            FreeLibrary(handle);
            continue;
        }

        LoadedPlugin lp;
        lp.name = desc.name;
        lp.desc = desc;
        lp.handle = handle;
        plugins.push_back(lp);

        std::cout << "Loaded plugin: " << desc.name
                  << " (" << desc.numArgs << " args)\n";
    }

    return !plugins.empty();
}

void PluginManager::UnloadAll()
{
    for (auto &p : plugins)
    {
        FreeLibrary(p.handle);
    }
    plugins.clear();
}
