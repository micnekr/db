#include "TokenCheckTemplate.h"

using namespace CustomClasses;

std::string toLowerCase(const std::string&);

void TokenCheckTemplate::initValueTokenChecker(const std::string& _tokenValue, bool _isCaseSensitive){
    isCaseSensitive = _isCaseSensitive;

    if(isCaseSensitive) tokenValue = _tokenValue;
    else tokenValue = toLowerCase(_tokenValue);

    tokenCheckTemplateType = TokenCheckTemplateTypes::Value;
}

TokenCheckTemplate::TokenCheckTemplate(const std::string& _tokenValue, bool _isCaseSensitive){

    initValueTokenChecker(_tokenValue, _isCaseSensitive);

    isUserDefined = true;
}

TokenCheckTemplate::TokenCheckTemplate(const std::string& _tokenValue, bool _isCaseSensitive, bool _isUserDefined){
    initValueTokenChecker(_tokenValue, _isCaseSensitive);
    isUserDefined = _isUserDefined;
}

TokenCheckTemplate::TokenCheckTemplate(TokenTypes _tokenType){
    tokenType = _tokenType;
    tokenCheckTemplateType = TokenCheckTemplateTypes::TokenType;
}

std::string toLowerCase(const std::string& in){
    std::string out;
    for(char i : in)
        out += std::tolower(i);
    return out;
}

bool TokenCheckTemplate::testToken(Token* token){
    
    //if by value
    switch (tokenCheckTemplateType)
    {
        case TokenCheckTemplateTypes::Value:
            if(!isUserDefined && token->type != GrammarSymbol) return false;
            if(isCaseSensitive) return token->contents == tokenValue;
            else return toLowerCase(token->contents) == tokenValue;
        case TokenCheckTemplateTypes::TokenType:
            return tokenType == token->type;
        default:
            return false;
    }
}