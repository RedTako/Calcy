#include "tokens.h"


TokenBase::TokenBase()
{

}

ValueToken::ValueToken(std::string content)
{
    this->content = content;
}

bool ValueToken::isOperator()
{
    return false;
}

double ValueToken::getValue() const
{
   return atof(content.c_str());
}



OperatorToken::OperatorToken(std::string content)
{
    this->content = content;
}

bool OperatorToken::isOperator()
{
    return true;
}

double OperatorToken::evaluate(const ValueToken &first, const ValueToken &second)
{
    return 0;
}



FunctionToken::FunctionToken(std::string content) : OperatorToken(content)
{

}

bool FunctionToken::isOperator()
{
    return true;
}

double FunctionToken::evaluate(const ValueToken &first, const ValueToken &second)
{
    return 0;
}
