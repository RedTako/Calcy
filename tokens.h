#ifndef TOKENS_H
#define TOKENS_H

#include <string>
#include <QString>
#include <unordered_map>

namespace std
{
    template<> struct hash<QString>
    {
        std::size_t operator()(const QString& s) const noexcept
        {
            const QChar* str = s.data();
            std::size_t hash = 5381;

            for (int i = 0; i < s.size(); ++i)
                hash = ((hash << 5) + hash) + ((str->row() << 8) | (str++)->cell());

            return hash;
        }
    };

    template<> struct hash<QChar>
    {
        std::size_t operator()(const QChar& s) const noexcept
        {
    //            const QChar* str = &s;
    //            std::size_t hash = 5381;

    //            hash = ((hash << 5) + hash) + ((str->row() << 8) | (str++)->cell());

            std::size_t hash ( std::hash<ushort>{}(s.unicode()) );

            return hash;
        }
    };
}

class TokenBase
{
public:
    enum TokenPrecedence : int
    {
        Brackets = 0,
        Operations,
        MultiplyDivide,
        PlusMinus,
        Number
    };

    static const std::unordered_map<QString, TokenPrecedence> strMap;
    TokenPrecedence getPrecedence() const;

    virtual bool isOperator() = 0;

    virtual const QString& getContent() const;
    virtual ~TokenBase();
protected:
    QString content;
    TokenPrecedence precedence;
    TokenBase();

};

class ValueToken : public TokenBase //numbers n stuff
{
public:
    ValueToken(const QString& content, TokenPrecedence precedence = TokenBase::Number);

    virtual bool isOperator() override;
    double getValue() const;

    virtual ~ValueToken() override;
};

class OperatorToken : public TokenBase //plus, divide
{                                      //simple operations
public:
    OperatorToken(const QString& content, TokenPrecedence precedence/* = TokenBase::Brackets*/);
    OperatorToken(const QString& content);

    virtual bool isOperator() override;
    virtual double evaluate(const double& first, const double& second);

    virtual ~OperatorToken() override;
};

class FunctionToken : public OperatorToken //sin and cos etc...
{
public:
    FunctionToken(const QString& content, TokenPrecedence precedence = TokenBase::Brackets);

    virtual bool isOperator() override;
    virtual double evaluate(const double& first, const double& second) override;

    virtual ~FunctionToken() override;
};


#endif // TOKENS_H
