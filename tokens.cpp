#include "tokens.h"
#include <streambuf>
#include <unordered_map>
#include <functional>
#include <math.h>

const std::unordered_map<QString, TokenBase::TokenPrecedence> TokenBase::strMap = {
{ QString::fromUtf16(u"+"), PlusMinus},
{ QString::fromUtf16(u"-"), PlusMinus},
{ QString::fromUtf16(u"x"), MultiplyDivide},
{ QString::fromUtf16(u"÷"), MultiplyDivide},
{ QString::fromUtf16(u"("), Brackets},
{ QString::fromUtf16(u")"), Brackets},
{ QString::fromUtf16(u"^"), Operations}
};


TokenBase::TokenPrecedence TokenBase::getPrecedence() const
{
    return this->precedence;
}

const QString &TokenBase::getContent() const
{
    return this->content;
}

TokenBase::~TokenBase()
{

}

TokenBase::TokenBase()
{

}

ValueToken::ValueToken(const QString& content, TokenPrecedence precedence)
{
    this->content = content;
    this->precedence = precedence;
}

bool ValueToken::isOperator()
{
    return false;
}

bool ValueToken::isFunction()
{
    return false;
}

double ValueToken::getValue() const
{
    return content.toDouble();
}

ValueToken::~ValueToken()
{

}


OperatorToken::OperatorToken(const QString& content)
{
    this->content = content;

    auto result = strMap.find(content);
    if(result == strMap.end())
        throw std::exception();

    this->precedence = result->second;
}

OperatorToken::OperatorToken(const QString& content, TokenPrecedence precedence)
{
    this->content = content;
    this->precedence = precedence;
}

bool OperatorToken::isOperator()
{
    return true;
}

bool OperatorToken::isFunction()
{
    return false;
}

double OperatorToken::evaluate(const double &first, const double &second)
{
    //typedef double(*Operation)(double, double);
    #define str16(x) QString::fromUtf16(x)

    auto add =      [](const double& a, const double& b) { return a + b; };
    auto minus =    [](const double& a, const double& b) { return a - b; };
    auto divide =   [](const double& a, const double& b) { return a / b; };
    auto multiply = [](const double& a, const double& b) { return a * b; };
    auto power =    [](const double& a, const double& b) { return pow(a, b); };

    const static std::unordered_map<QString, std::function<double(double, double)>> map =
    {
        { str16(u"+"), add },
        { str16(u"-"), minus },
        { str16(u"÷"), divide },
        { str16(u"x"), multiply },
        { str16(u"^"), power}
    };

    auto result = map.find(this->content);
    if(result == map.end())
        throw std::exception();

//    double d1, d2;
//    d1 = first.getValue();
//    d2 = second.getValue();

    return (*result).second(first, second);
}

OperatorToken::~OperatorToken()
{

}



FunctionToken::FunctionToken(const QString& content)
{
    this->content = content;
    this->precedence = TokenPrecedence::Operations;
}

bool FunctionToken::isOperator()
{
    return false;
}

bool FunctionToken::isFunction()
{
    return true;
}

double FunctionToken::evaluate(const double& value)
{
    static const std::unordered_map<QString, std::function<double(double)>> map =
    {

    };
    return 0;
}

FunctionToken::~FunctionToken()
{

}
