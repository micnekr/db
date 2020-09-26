#ifndef PARSER_H // include guard
#define PARSER_H

#include "TokenCheckTemplate.h"
#include "Token.h"
#include "ParserRule.h"

#include <iostream>

namespace CustomClasses{

    class Parser{
        public:
        static std::vector<ParserRule*> grammarRules;
        static void init();
        static Token* parse(std::vector<Token*>m);
        private:
        static bool reduce(std::vector<Token*>&, Token*);
    };
}
#endif