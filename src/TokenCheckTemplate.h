#ifndef TOKEN_CHECK_TEMPLATE_H // include guard
#define TOKEN_CHECK_TEMPLATE_H

#include "Token.h"
#include <string>
#include <locale>

namespace CustomClasses{

    enum TokenCheckTemplateTypes{
        Value,
        TokenType
    };
    class TokenCheckTemplate{
        public:
        TokenCheckTemplate(std::string, bool);
        TokenCheckTemplate(std::string, bool, bool);
        TokenCheckTemplate(TokenTypes);
        bool testToken(Token*);
        bool isUserDefined; // can a user use this token in a command and will it be seen as one?
        private:
        TokenCheckTemplateTypes tokenCheckTemplateType;
        bool isCaseSensitive;
        std::string tokenValue;
        TokenTypes tokenType;
        void initValueTokenChecker(std::string, bool);
    };
}
#endif