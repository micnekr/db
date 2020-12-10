#include "ParserRule.h"

using namespace CustomClasses;

ParserRule::ParserRule(std::vector<TokenCheckTemplate*>* _inputTokens, Token* _outputToken){
    inputTokens = _inputTokens;
    outputToken = _outputToken;
    isUsingLookAhead = false;
    lookAhead = nullptr;
}

ParserRule::ParserRule(std::vector<TokenCheckTemplate*>* _inputTokens, Token* _outputToken, std::vector<TokenCheckTemplate*>* _lookAhead){
    inputTokens = _inputTokens;
    outputToken = _outputToken;
    lookAhead = _lookAhead;
    isUsingLookAhead = true;
}