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
            case '*':
            case '/':
            case '^':
                tokens.push_back({calc::TokenType::Operator, std::string(1, c)});
                break;
            case '-':
            {
                if (tokens.empty())
                {
                    tokens.push_back({calc::TokenType::Operator, std::string("u-")});
                    break;
                }
                else
                {
                    calc::TokenType prev = tokens.back().type;
                    if (prev == calc::TokenType::Operator || prev == calc::TokenType::LParen || prev == calc::TokenType::Comma)
                    {
                        tokens.push_back({calc::TokenType::Operator, std::string("u-")});
                        break;
                    }
                    else
                    {
                        tokens.push_back({calc::TokenType::Operator, std::string("-")});
                        break;
                    }
                }
            }
            case '(':
                tokens.push_back({calc::TokenType::LParen, "("});
                break;
            case ')':
                tokens.push_back({calc::TokenType::RParen, ")"});
                break;
            case ',':
                tokens.push_back({calc::TokenType::Comma, ","});
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

static bool is_right_sided(const std::string &op)
{
    if (op == "^")
        return true;
    if (op == "u-")
        return true;
    return false;
}

static int precedence(const std::string &op)
{
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    if (op == "u-")
        return 3;
    if (op == "^")
        return 4;
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
            while (!ops.empty() && ops.top().type == TokenType::Operator)
            {
                const std::string &topOp = ops.top().text;
                int pTop = precedence(topOp);
                int pCurr = precedence(tok.text);

                if ((!is_right_sided(tok.text) && pTop >= pCurr) || (is_right_sided(tok.text) && pTop > pCurr))
                {
                    output.push_back(ops.top());
                    ops.pop();
                }
                else
                {
                    break;
                }
            }
            ops.push(tok);
            break;

        case calc::TokenType::Comma:
            while (!ops.empty() && ops.top().type != calc::TokenType::LParen)
            {
                output.push_back(ops.top());
                ops.pop();
            }
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
