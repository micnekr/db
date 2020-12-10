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
        TokenCheckTemplate(const std::string&, bool);
        TokenCheckTemplate(const std::string&, bool, bool);
        explicit TokenCheckTemplate(TokenTypes);
        bool testToken(Token*);
        bool isUserDefined; // can a user use this token in a command and will it be seen as one?
        private:
        TokenCheckTemplateTypes tokenCheckTemplateType;
        bool isCaseSensitive;
        std::string tokenValue;
        TokenTypes tokenType;
        void initValueTokenChecker(const std::string&, bool);
    };
}
#endif