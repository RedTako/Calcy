#include "tokenizer.h"

#include <unordered_map>
#include <unordered_set>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <algorithm>
#include <stack>


Tokenizer::Tokenizer()
{

}

const std::vector<Tokenizer::TokenPtr>& Tokenizer::getTokenList() const
{
    return tokenList;
}

const std::vector<Tokenizer::TokenPtr> &Tokenizer::tokenize(QString str)
{
#define str(x) QString(x)


    if(tokenList.size() > 0)
        tokenList.clear();


    std::stack<QChar> numStack;

    auto tokenizeNumberString = [&]()
    {
        if(numStack.size() > 0) //if elem in stack
        {
            QString container = "";
            int stackSize = numStack.size();
            for(int j = 0; j < stackSize; j++)
            {
                container.push_front(numStack.top());
                numStack.pop();
            }
            tokenList.push_back(std::make_unique<ValueToken>(container));
        }
    };

    for(int i = 0; i < str.length(); i++)
    {
        QChar c = str[i];
        auto result = TokenBase::strMap.find(c);
        if(result == TokenBase::strMap.end()) //no match
        {
            numStack.push(c);
        }
        else
        {
            tokenizeNumberString();
            tokenList.push_back(std::make_unique<OperatorToken>(QString(str[i])));
        }
        if(i == str.length() - 1)
        {
            tokenizeNumberString();
        }
    }


    return tokenList;

}

std::vector<Tokenizer::TokenRef> &Tokenizer::sortByPrecedence()
{
//    typedef std::vector<TokenRef> tokenVec;

//    auto swap = [](TokenRef& a, TokenRef& b)
//    {
//        TokenRef buffer = a;
//        a = b;
//        b = buffer;
//    };



//    int i = 1;
//    tokenVec& vec = tokenList;
//    while (i < tokenList.size())
//    {
//        int j = i;
//        TokenRef t1 = vec[j-1];
//        TokenRef t2 = vec[j];
//        while(j > 0 && (t1.get().getPrecedence() > t2.get().getPrecedence()))
//        {
//            swap(t1, t2);
//        }

//    }

//    return vec;
    throw std::exception();
}

const char *NoMatchException::what() const noexcept
{
    return errorMsg;
}
