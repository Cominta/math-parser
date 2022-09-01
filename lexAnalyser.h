#ifndef LEX_ANALYSER_H
#define LEX_ANALYSER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

class LexAnalyser
{
    public:
        enum class TokenType
        {
            NUM,
            PLUS,
            SUB,
            DIVIDE,
            MULTIPLY,
            LB,
            RB,
            END,
            UNKNOWN
        };

    private:
        std::map<char, TokenType> mapTokens = {
            {'+', TokenType::PLUS},
            {'-', TokenType::SUB},
            {'/', TokenType::DIVIDE},
            {'*', TokenType::MULTIPLY},
            {'(', TokenType::LB},
            {')', TokenType::RB}
        };

    public:
        struct Token
        {
            TokenType tType;
            int value = 0;
        };

        LexAnalyser();
        ~LexAnalyser();

        std::vector<Token*> analyseString(std::string inputString, int index);
};

#endif 