#include "plugin_api.h"
#include <cmath>

static PluginError log_func(int argCount, double* args, double* result)
{
    if (argCount != 2)
        return PLUGIN_ERROR_ARGS_COUNT;

    double base = args[0];
    double value = args[1];

    if (base <= 0 || base == 1.0 || value <= 0)
        return PLUGIN_ERROR_MATH;

    *result = std::log(value) / std::log(base);
    return PLUGIN_OK;
}

PLUGIN_API FunctionDescriptor GetFunctionDescriptor()
{
    FunctionDescriptor d;
    d.name = "log";
    d.numArgs = 2;
    d.ptr = log_func;
    return d;
}