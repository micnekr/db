#ifndef LEXER_H // include guard
#define LEXER_H

#include "Token.h"

#include <iostream>
#include <list>
#include <string>

namespace CustomClasses{

    class Lexer{
        public:
            static std::list<Token*> tokenize(std::string);
            static TokenTypes lexerToTokenTypes(TokenTypes);
            static bool isWhitespaceChar(char);
            static bool isOperatorChar(char);
    };
}

#endif