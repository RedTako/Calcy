#ifndef TOKENS_H
#define TOKENS_H

#include <string>


class TokenBase
{
public:
    enum TokenPrecedence
    {
        Brackets,

    };

    std::string content;

    virtual bool isOperator() = 0;
protected:

    TokenBase();

};

class ValueToken : public TokenBase //numbers n stuff
{
public:
    ValueToken(std::string content);

    virtual bool isOperator() override;
    double getValue() const;
};

class OperatorToken : public TokenBase //plus, divide
{                                      //simple operations
public:
    OperatorToken(std::string content);

    virtual bool isOperator() override;
    virtual double evaluate(const ValueToken& first, const ValueToken& second);
};

class FunctionToken : public OperatorToken //sin and cos etc...
{
public:
    FunctionToken(std::string content);

    virtual bool isOperator() override;
    virtual double evaluate(const ValueToken& first, const ValueToken& second) override;
};


#endif // TOKENS_H
