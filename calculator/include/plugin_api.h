#ifndef PLUGIN_API_H
#define PLUGIN_API_H

#ifdef BUILDING_PLUGIN_DLL
#define PLUGIN_API extern "C" __declspec(dllexport)
#else
#define PLUGIN_API extern "C" __declspec(dllimport)
#endif

//  error codes for plugin
enum PluginError
{
    PLUGIN_OK,
    PLUGIN_ERROR_MATH,
    PLUGIN_ERROR_ARGS_COUNT
};

//  single type for every plugin
typedef PluginError (*PluginFunction)(int argCount, double *args, double *result);

struct FunctionDescriptor
{
    const char *name;
    int numArgs;
    PluginFunction ptr;
};

PLUGIN_API FunctionDescriptor GetFunctionDescriptor();

#endif