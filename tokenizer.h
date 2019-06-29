#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <memory>

#include "tokens.h"

class Tokenizer
{
public:
    Tokenizer();
    typedef std::unique_ptr<TokenBase> TokenPtr;


    std::vector<TokenPtr>& tokenize(std::string str);
private:
    std::vector<TokenPtr> tokenList;
};



#endif // TOKENIZER_H
