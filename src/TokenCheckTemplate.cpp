#include "TokenCheckTemplate.h"

using namespace CustomClasses;

std::string toLowerCase(std::string);

void TokenCheckTemplate::initValueTokenChecker(std::string _tokenValue, bool _isCaseSensitive){
    isCaseSensitive = _isCaseSensitive;

    if(isCaseSensitive) tokenValue = _tokenValue;
    else tokenValue = toLowerCase(_tokenValue);

    tokenCheckTemplateType = TokenCheckTemplateTypes::Value;
}

TokenCheckTemplate::TokenCheckTemplate(std::string _tokenValue, bool _isCaseSensitive){

    initValueTokenChecker(_tokenValue, _isCaseSensitive);

    isUserDefined = true;
}

TokenCheckTemplate::TokenCheckTemplate(std::string _tokenValue, bool _isCaseSensitive, bool _isUserDefined){
    initValueTokenChecker(_tokenValue, _isCaseSensitive);
    isUserDefined = _isUserDefined;
}

TokenCheckTemplate::TokenCheckTemplate(TokenTypes _tokenType){
    tokenType = _tokenType;
    tokenCheckTemplateType = TokenCheckTemplateTypes::TokenType;
}

std::string toLowerCase(std::string in){
    std::string out = "";
    for(int i = 0; i < in.size(); i++)
        out += std::tolower(in[i]);
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