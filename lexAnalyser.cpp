#include "lexAnalyser.h"

LexAnalyser::LexAnalyser()
{

}

LexAnalyser::~LexAnalyser()
{
    
}

std::vector<LexAnalyser::Token*> LexAnalyser::analyseString(std::string inputString, int index)
{
    int i = index;
    std::vector<LexAnalyser::Token*> output;

    while (inputString[i] != '$')
    {
        LexAnalyser::Token* currentToken = new LexAnalyser::Token();

        if (isdigit(inputString[i]))
        {
            int num = inputString[i] - '0';
            i++;

            while (isdigit(inputString[i]))
            {
                num *= 10;
                num += inputString[i] - '0';
                i++;
            }
            
            currentToken->value = num;
            currentToken->tType = LexAnalyser::TokenType::NUM;
        }

        else 
        {
            currentToken->tType = this->mapTokens[inputString[i]];
            i++;
        }

        output.push_back(currentToken);
    }

    LexAnalyser::Token* endToken = new Token();
    endToken->tType = LexAnalyser::TokenType::END;
    output.push_back(endToken);

    return output;
}