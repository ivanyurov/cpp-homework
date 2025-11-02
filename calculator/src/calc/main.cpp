#include <iostream>
#include "plugin_loader.hpp"
#include "evaluator.hpp"

int main()
{
    std::string pluginDir = "./plugins";

    PluginManager manager;
    manager.LoadAll(pluginDir);

    std::vector<FunctionDescriptor> funcs;
    for (auto &p : manager.GetFunctions())
        funcs.push_back(p.desc);

    Evaluator eval(funcs);

    std::string expr;
    while (true)
    {
        std::cout << "\n> ";
        std::getline(std::cin, expr);
        if (expr == "exit" || expr == "quit")
            break;

        auto tokens = calc::Parser::Tokenize(expr);
        auto rpn = calc::Parser::ToRPN(tokens);

        double result = 0;
        std::string err;
        if (eval.Evaluate(rpn, result, err))
            std::cout << " = " << result << "\n";
        else
            std::cout << "Error: " << err << "\n";
    }

    manager.UnloadAll();
    return 0;
}
