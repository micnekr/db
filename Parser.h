#ifndef PARSER_H // include guard
#define PARSER_H

#include "TokenCheckTemplate.h"
#include "Token.h"
#include "ParserRule.h"

#include <iostream>
#include <list>
#include <vector>

namespace CustomClasses{

    class Parser{
        public:
        static std::vector<ParserRule*> grammarRules;
        static void init();
        static Token* parse(std::list<Token*>m);
        private:
        static bool reduce(std::list<Token*>&, Token*);
    };
}
#endif