#include "parser.hpp"
#include <cctype>
#include <stack>
#include <iostream>

std::vector<calc::Token> calc::Parser::Tokenize(const std::string &expr)
{
    std::vector<calc::Token> tokens;
    for (size_t i = 0; i < expr.size();)
    {
        char c = expr[i];
        if (std::isspace(c))
        {
            ++i;
            continue;
        }

        if (std::isdigit(c) || (c == '.' && i + 1 < expr.size() && std::isdigit(expr[i + 1])))
        {
            std::string num;
            while (i < expr.size() && (std::isdigit(expr[i]) || expr[i] == '.'))
            {
                num += expr[i++];
            }
            tokens.push_back({calc::TokenType::Number, num, std::stod(num)});
        }
        else if (std::isalpha(c))
        {
            std::string name;
            while (i < expr.size() && std::isalpha(expr[i]))
            {
                name += expr[i++];
            }
            tokens.push_back({calc::TokenType::Function, name, 0});
        }
        else
        {
            switch (c)
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                tokens.push_back({calc::TokenType::Operator, std::string(1, c)});
                break;
            case '(':
                tokens.push_back({calc::TokenType::LParen, "("});
                break;
            case ')':
                tokens.push_back({calc::TokenType::RParen, ")"});
                break;
            default:
                std::cerr << "Unknown character: " << c << "\n";
                break;
            }
            ++i;
        }
    }
    return tokens;
}

static int precedence(const std::string &op)
{
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    if (op == "^")
        return 3;
    return 0;
}

//  shunting yard
std::vector<calc::Token> calc::Parser::ToRPN(const std::vector<Token> &tokens)
{
    std::vector<calc::Token> output;
    std::stack<calc::Token> ops;

    for (auto &tok : tokens)
    {
        switch (tok.type)
        {
        case calc::TokenType::Number:
            output.push_back(tok);
            break;

        case calc::TokenType::Function:
            ops.push(tok);
            break;

        case calc::TokenType::Operator:
            while (!ops.empty() && ops.top().type == calc::TokenType::Operator &&
                   precedence(ops.top().text) >= precedence(tok.text))
            {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(tok);
            break;

        case calc::TokenType::LParen:
            ops.push(tok);
            break;

        case calc::TokenType::RParen:
            while (!ops.empty() && ops.top().type != calc::TokenType::LParen)
            {
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty() && ops.top().type == calc::TokenType::LParen)
                ops.pop();
            if (!ops.empty() && ops.top().type == calc::TokenType::Function)
            {
                output.push_back(ops.top());
                ops.pop();
            }
            break;
        }
    }

    while (!ops.empty())
    {
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}
