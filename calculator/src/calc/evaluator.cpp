#include "evaluator.hpp"
#include <stack>
#include <cmath>
#include <iostream>

Evaluator::Evaluator(const std::vector<FunctionDescriptor> &f)
{
    for (auto &fn : f)
        funcs[fn.name] = fn;
}

bool Evaluator::Evaluate(const std::vector<calc::Token> &rpn, double &result, std::string &errorMsg)
{
    std::stack<double> st;

    for (auto &tok : rpn)
    {
        if (tok.type == calc::TokenType::Number)
        {
            st.push(tok.value);
        }
        else if (tok.type == calc::TokenType::Operator)
        {
            if (tok.text == "u-")
            {
                if (st.empty())
                {
                    errorMsg = "Invalid expression (unary -)";
                    return false;
                }
                double a = st.top();
                st.pop();
                st.push(-a);
            }
            else
            {
                if (st.size() < 2)
                {
                    errorMsg = "Invalid expression";
                    return false;
                }
                double b = st.top();
                st.pop();
                double a = st.top();
                st.pop();
                double res = 0;

                if (tok.text == "+")
                    res = a + b;
                else if (tok.text == "-")
                    res = a - b;
                else if (tok.text == "*")
                    res = a * b;
                else if (tok.text == "/")
                {
                    if (b == 0)
                    {
                        errorMsg = "Division by zero";
                        return false;
                    }
                    res = a / b;
                }
                else if (tok.text == "^")
                {
                    res = std::pow(a, b);
                }
                else
                {
                    errorMsg = "Unknown operator: " + tok.text;
                    return false;
                }

                st.push(res);
            }
        }
        else if (tok.type == calc::TokenType::Function)
        {
            auto it = funcs.find(tok.text);
            if (it == funcs.end())
            {
                errorMsg = "Unknown function: " + tok.text;
                return false;
            }

            auto &desc = it->second;
            if ((int)st.size() < desc.numArgs)
            {
                errorMsg = "Not enough arguments for " + tok.text;
                return false;
            }

            double args[4];
            for (int i = desc.numArgs - 1; i >= 0; --i)
            {
                args[i] = st.top();
                st.pop();
            }

            double res = 0;
            PluginError err = desc.ptr(desc.numArgs, args, &res);
            if (err != PLUGIN_OK)
            {
                errorMsg = "Error in function " + tok.text;
                return false;
            }

            st.push(res);
        }
    }

    if (st.size() != 1)
    {
        errorMsg = "Invalid expression result stack";
        return false;
    }

    result = st.top();
    return true;
}
