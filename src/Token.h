#ifndef TOKEN_H // include guard
#define TOKEN_H

#include <string>
#include <vector>
#include <iostream>

namespace CustomClasses{

    enum TokenTypes {
        NoToken,

        Identifer,
        Number,
        String,
        OperatorSymbols,
        RoundBracket,

        Comment,

        GrammarSymbol,

        NullToken
    };

    class Token{
        public:
        std::string contents;
        TokenTypes type;
        std::vector<Token*> children;
        Token(std::string, TokenTypes);
        explicit Token(std::string);
        void addChild(Token*);
        void setChildren(std::vector<Token*>);
        [[nodiscard]] std::string print(int) const;

        ~Token();
    };
}

std::ostream& operator<<(std::ostream &, const CustomClasses::Token &);

#endif