#include "plugin_api.h"
#include <cmath>

static PluginError ln_func(int argCount, double *args, double *result)
{
    if (argCount != 1)
        return PLUGIN_ERROR_ARGS_COUNT;

    double x = args[0];
    if (x <= 0)
        return PLUGIN_ERROR_MATH;

    *result = std::log(x);
    return PLUGIN_OK;
}

PLUGIN_API FunctionDescriptor GetFunctionDescriptor()
{
    FunctionDescriptor d;
    d.name = "ln";
    d.numArgs = 1;
    d.ptr = ln_func;
    return d;
}