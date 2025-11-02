#pragma once
#include <map>
#include <vector>
#include <string>
#include "parser.hpp"
#include "plugin_api.h"

class Evaluator
{
public:
    Evaluator(const std::vector<FunctionDescriptor> &funcs);
    bool Evaluate(const std::vector<calc::Token> &rpn, double &result, std::string &errorMsg);

private:
    std::map<std::string, FunctionDescriptor> funcs;
};
