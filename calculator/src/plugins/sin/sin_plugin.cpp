#define _USE_MATH_DEFINES
#include <cmath>
#include "plugin_api.h"

static PluginError sin_func(int argc, double *args, double *result)
{
    if (argc != 1)
        return PLUGIN_ERROR_ARGS_COUNT;
    *result = std::sin(args[0] * M_PI / 180.0);
    return PLUGIN_OK;
}

PLUGIN_API FunctionDescriptor GetFunctionDescriptor()
{
    FunctionDescriptor d;
    d.name = "sin";
    d.numArgs = 1;
    d.ptr = sin_func;
    return d;
}
