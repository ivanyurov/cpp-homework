#include "parser.hpp"
#include "evaluator.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << "type 'exit' or 'quit' to exit:\n";

    std::string expr;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, expr);

        if (expr == "exit" || expr == "quit")
            break;

        if (expr.empty())
            continue;

        auto tokens = Parser::Tokenize(expr);
        auto rpn = Parser::ToRPN(tokens);
        double result = Evaluator::Evaluate(rpn);

        std::cout << "= " << result << "\n";
    }

    return 0;
}
