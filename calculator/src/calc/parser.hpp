#pragma once
#include <string>
#include <vector>

namespace calc
{

    enum class TokenType
    {
        Number,
        Operator,
        Function,
        LParen,
        RParen
    };

    struct Token
    {
        TokenType type;
        std::string text;
        double value = 0;
    };

    class Parser
    {
    public:
        static std::vector<Token> Tokenize(const std::string &expr);
        static std::vector<Token> ToRPN(const std::vector<Token> &tokens);
    };
}
