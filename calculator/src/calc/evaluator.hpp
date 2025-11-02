#pragma once
#include <vector>
#include <string>
#include "parser.hpp"

class Evaluator {
public:
    static double Evaluate(const std::vector<Token>& rpn);
};