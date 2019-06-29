#include "tokenizer.h"

#include <unordered_map>
#include <QString>


Tokenizer::Tokenizer()
{

}

std::vector<Tokenizer::TokenPtr>& Tokenizer::tokenize(std::string str)
{
#define str(x) QString(x)
#define str16(x) QString::fromUtf16(x)

    enum StringResult
    {
        Plus,           LeftBracket,
        Minus,          RightBracket,
        Divide,
        Multiply,
    };

    const std::unordered_map<std::basic_string<char16_t>, StringResult> strMap = {
        {u"+", Plus},
        {u"-", Minus},
        {u"*", Multiply},
        {u"÷", Divide},
        {u"(", LeftBracket},
        {u")", RightBracket}

    };




    switch (strMap.at(str))
    {
        case Plus:
            break;

        case Minus:
            break;

        case Divide:
            break;

        case Multiply:
            break;

        case LeftBracket:
            break;

        case RightBracket:
            break;
    }





    throw std::exception();

}
