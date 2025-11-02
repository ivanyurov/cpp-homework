#define _USE_MATH_DEFINES
#include <cmath>
#include "plugin_api.h"

static PluginError cos_func(int argc, double *args, double *result)
{
    if (argc != 1)
        return PLUGIN_ERROR_ARGS_COUNT;
    *result = std::cos(args[0] * M_PI / 180.0);
    return PLUGIN_OK;
}

PLUGIN_API FunctionDescriptor GetFunctionDescriptor()
{
    FunctionDescriptor d;
    d.name = "cos";
    d.numArgs = 1;
    d.ptr = cos_func;
    return d;
}
