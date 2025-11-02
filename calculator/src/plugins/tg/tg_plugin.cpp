#define _USE_MATH_DEFINES
#include <cmath>
#include "plugin_api.h"

static PluginError tg_func(int argc, double *args, double *result)
{
    if (argc != 1)
        return PLUGIN_ERROR_ARGS_COUNT;

    double tmp_cos = std::cos(args[0] * M_PI / 180.0);
    double tmp_sin = std::sin(args[0] * M_PI / 180.0);

    if (tmp_cos == (double)0)
    {
        return PLUGIN_ERROR_MATH;
    }
    *result = tmp_sin / tmp_cos;
    return PLUGIN_OK;
}

PLUGIN_API FunctionDescriptor GetFunctionDescriptor()
{
    FunctionDescriptor d;
    d.name = "tg";
    d.numArgs = 1;
    d.ptr = tg_func;
    return d;
}