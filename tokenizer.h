#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <memory>
#include <QString>

#include "tokens.h"

class Tokenizer
{
public:
    Tokenizer();

    Tokenizer(const Tokenizer&) = delete;


    typedef std::unique_ptr<TokenBase> TokenPtr;
    typedef std::reference_wrapper<TokenBase> TokenRef;


    const std::vector<TokenPtr>& getTokenList() const;
    const std::vector<TokenPtr>& tokenize(QString str);

    std::vector<TokenRef>& sortByPrecedence();
private:
    std::vector<TokenPtr> tokenList;
};

class NoMatchException : std::exception
{
protected:
    const char* errorMsg;
public:
    NoMatchException(const char* msg);
    const char* what() const noexcept override;

};


#endif // TOKENIZER_H
