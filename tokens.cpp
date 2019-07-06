#include "tokens.h"
#include <streambuf>
#include <unordered_map>
#include <functional>

const std::unordered_map<QString, TokenBase::TokenPrecedence> TokenBase::strMap = {
{ QString::fromUtf16(u"+"), PlusMinus},
{ QString::fromUtf16(u"-"), PlusMinus},
{ QString::fromUtf16(u"x"), MultiplyDivide},
{ QString::fromUtf16(u"÷"), MultiplyDivide},
{ QString::fromUtf16(u"("), Brackets},
{ QString::fromUtf16(u")"), Brackets}
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

//    const std::unordered_map<QString, TokenPrecedence> strMap = {
//        { QString::fromUtf16(u"+"), PlusMinus},
//        { QString::fromUtf16(u"-"), PlusMinus},
//        { QString::fromUtf16(u"x"), MultiplyDivide},
//        { QString::fromUtf16(u"÷"), MultiplyDivide},
//        { QString::fromUtf16(u"("), Brackets},
//        { QString::fromUtf16(u")"), Brackets}
//    };

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



double OperatorToken::evaluate(const double &first, const double &second)
{
    //typedef double(*Operation)(double, double);
    #define str16(x) QString::fromUtf16(x)

    auto add =      [](const double& a, const double& b) { return a + b; };
    auto minus =    [](const double& a, const double& b) { return a - b; };
    auto divide =   [](const double& a, const double& b) { return a / b; };
    auto multiply = [](const double& a, const double& b) { return a * b; };

    const std::unordered_map<QString, std::function<double(double, double)>> map =
    {
        { str16(u"+"), add },
        { str16(u"-"), minus },
        { str16(u"÷"), divide },
        { str16(u"x"), multiply }
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



FunctionToken::FunctionToken(const QString& content, TokenPrecedence precedence) :
    OperatorToken(content, precedence)
{

}

bool FunctionToken::isOperator()
{
    return true;
}

double FunctionToken::evaluate(const double &first, const double &second)
{
    return 0;
}

FunctionToken::~FunctionToken()
{

}
