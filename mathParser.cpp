#include "mathParser.h"

MathParser::MathParser()
{
    this->lexanalyser = new LexAnalyser();
}

MathParser::~MathParser()
{
    
}

void MathParser::printExpr(std::vector<LexAnalyser::Token*> tokenArray)
{
    for (auto token : tokenArray)
    {
        if (token->tType == LexAnalyser::TokenType::NUM)
        {
            std::cout << token->value;
        }

        else 
        {
            switch (token->tType)
            {
                case LexAnalyser::TokenType::PLUS:
                    std::cout << "+";
                    break;

                case LexAnalyser::TokenType::SUB:
                    std::cout << "-";
                    break;

                case LexAnalyser::TokenType::DIVIDE:
                    std::cout << "/";
                    break;

                case LexAnalyser::TokenType::MULTIPLY:
                    std::cout << "*";
                    break;

                case LexAnalyser::TokenType::LB:
                    std::cout << "(";
                    break;

                case LexAnalyser::TokenType::RB:
                    std::cout << ")";
                    break;
            }
        }
    }
}

void MathParser::calculateStack(std::stack<double>& numbers, std::stack<LexAnalyser::TokenType>& op, LexAnalyser::TokenType currentOp, bool RB)
{
    bool endStack = (currentOp == LexAnalyser::TokenType::END);

    while (!op.empty() && (endStack || this->priority[op.top()] >= this->priority[currentOp]) || RB)
    {
        if (op.top() == LexAnalyser::TokenType::LB)
        {
            break;
        }

        double num1 = numbers.top();
        numbers.pop();

        double num2 = numbers.top();
        numbers.pop();

        switch (op.top())
        {

            case LexAnalyser::TokenType::PLUS:
                numbers.push(num1 + num2);
                break;

            case LexAnalyser::TokenType::SUB:
                numbers.push(num2 - num1);
                break;

            case LexAnalyser::TokenType::MULTIPLY:
                numbers.push(num1 * num2);
                break;

            case LexAnalyser::TokenType::DIVIDE:
                numbers.push(num2 / num1);
                break;
        }

        op.pop();
    }
}

double MathParser::calculate(std::vector<LexAnalyser::Token*> tokenArray)
{
    std::stack<double> numbers;
    std::stack<LexAnalyser::TokenType> op;

    int i = 0;

    while (tokenArray[i]->tType != LexAnalyser::TokenType::END)
    {
        LexAnalyser::Token* currentToken = tokenArray[i];

        if (currentToken->tType == LexAnalyser::TokenType::NUM)
        {
            numbers.push(currentToken->value);
        }

        else if (currentToken->tType == LexAnalyser::TokenType::RB)
        {
            this->calculateStack(numbers, op, LexAnalyser::TokenType::UNKNOWN, true);
        }

        else if (!op.empty() && this->priority[op.top()] >= this->priority[currentToken->tType])
        {
            this->calculateStack(numbers, op, currentToken->tType);
            op.push(currentToken->tType);
        }

        else 
        {
            op.push(currentToken->tType);
        }

        i++;
    }

    this->calculateStack(numbers, op);
    std::cout << numbers.top();

    return 0;
}

double MathParser::parseString(std::string inputString, int index)
{
    this->inputString = inputString + "$";
    this->currentIndex = index;

    std::vector<LexAnalyser::Token*> tokenArray = this->lexanalyser->analyseString(this->inputString, this->currentIndex);

    this->calculate(tokenArray);
}