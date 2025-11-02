#include "evaluator.hpp"
#include <stack>
#include <cmath>
#include <iostream>

double Evaluator::Evaluate(const std::vector<Token>& rpn) {
    std::stack<double> st;

    for (const auto& tok : rpn) {
        if (tok.type == TokenType::Number) {
            st.push(tok.value);
        }
        else if (tok.type == TokenType::Operator) {
            if (st.size() < 2) {
                std::cerr << "Error: not enough operands for operator " << tok.text << "\n";
                return 0;
            }

            double b = st.top(); st.pop();
            double a = st.top(); st.pop();

            if (tok.text == "+") st.push(a + b);
            else if (tok.text == "-") st.push(a - b);
            else if (tok.text == "*") st.push(a * b);
            else if (tok.text == "/") {
                if (b == 0) {
                    std::cerr << "Error: division by zero\n";
                    return 0;
                }
                st.push(a / b);
            }
            else if (tok.text == "^") {
                st.push(std::pow(a, b));
            }
            else {
                std::cerr << "Unknown operator: " << tok.text << "\n";
                return 0;
            }
        }
        else {
            std::cerr << "Invalid token in RPN sequence: " << tok.text << "\n";
            return 0;
        }
    }

    if (st.size() != 1) {
        std::cerr << "Error: invalid expression\n";
        return 0;
    }

    return st.top();
}
