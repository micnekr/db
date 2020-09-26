#ifndef PARSER_RULE_H // include guard
#define PARSER_RULE_H

#include "TokenCheckTemplate.h"
#include "Token.h"
#include <iostream>

namespace CustomClasses{

    class ParserRule{
        public:
        std::vector<TokenCheckTemplate*>* inputTokens;
        Token* outputToken;
        std::vector<TokenCheckTemplate*>* lookAhead;

        bool isUsingLookAhead;
        ParserRule(std::vector<TokenCheckTemplate*>*, Token*);
        ParserRule(std::vector<TokenCheckTemplate*>*, Token*, std::vector<TokenCheckTemplate*>*);
    };
}

#endif