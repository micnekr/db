#include "Parser.h"

using namespace CustomClasses;

std::vector<ParserRule*> Parser::grammarRules;
Token* nullToken;
TokenCheckTemplate* shiftTokenCheckTemplate = new TokenCheckTemplate("SHIFT", true, false);

Token* smartLookAhead(std::list<Token*>& parseStack, Token* nextToken, std::list<Token*>::iterator i){
    //check if it is the last element
    if((i != parseStack.end()) && (next(i) == parseStack.end())) return nextToken;
    else return *next(i);
}

void Parser::init(){
    nullToken = new Token("", TokenTypes::NullToken);
    Parser::grammarRules.clear();

    ParserRule* rule;

    std::vector<TokenCheckTemplate*>* inputs;
    Token* output;
    std::vector<TokenCheckTemplate*>* lookAhead;

    //addressing

    //Identifier->id
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate(TokenTypes::Identifer)});
    output = new Token("ID");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //.->dot
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate(".", false)});
    output = new Token("DOT");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //id dot id->id
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("ID", true, false), new TokenCheckTemplate("DOT", true, false), new TokenCheckTemplate("ID", true, false)});
    output = new Token("ID");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //arithmetics
    //number->VAL
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate(TokenTypes::Number)});
    output = new Token("VAL");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //string->VAL
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate(TokenTypes::String)});
    output = new Token("VAL");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //+->BINARYOP1
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("+", false)});
    output = new Token("BINARYOP1");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //-->BINARYOP1
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("-", false)});
    output = new Token("BINARYOP1");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //*->BINARYOP2
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("*", false)});
    output = new Token("BINARYOP2");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    ///->BINARYOP2
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("/", false)});
    output = new Token("BINARYOP2");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //other rules
    //(VAL)->bracket_expression
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("(", false), new TokenCheckTemplate("VAL", true, false), new TokenCheckTemplate(")", false)});
    output = new Token("BRACKET_EXPRESSION");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);
    //()->bracket_expression
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("(", false), new TokenCheckTemplate(")", false)});
    output = new Token("BRACKET_EXPRESSION");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //(ARRAY_PART)->bracket_expression
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("(", false), new TokenCheckTemplate("ARRAY_PART", true, false), new TokenCheckTemplate(")", false)});
    output = new Token("BRACKET_EXPRESSION");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //id bracket_expression->id
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("ID", true, false), new TokenCheckTemplate("BRACKET_EXPRESSION", true, false)});
    output = new Token("ID");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //bracket_expression->VAL
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("BRACKET_EXPRESSION", true, false)});
    output = new Token("VAL");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //VAL, VAL->ARRAY_PART
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("VAL", true, false), new TokenCheckTemplate(",", false), new TokenCheckTemplate("VAL", true, false)});
    output = new Token("ARRAY_PART");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //ARRAY_PART, VAL->ARRAY_PART
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("ARRAY_PART", true, false), new TokenCheckTemplate(",", false), new TokenCheckTemplate("VAL", true, false)});
    output = new Token("ARRAY_PART");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //VAL->shift if lookahead is an operator
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("VAL", true, false)});
    output = new Token("SHIFT");
    lookAhead = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("BINARYOP1", true, false), new TokenCheckTemplate("BINARYOP2", true, false)});
    rule = new ParserRule(inputs, output, lookAhead);
    Parser::grammarRules.push_back(rule);

    //VAL binaryOp2 VAL->VAL
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("VAL", true, false), new TokenCheckTemplate("BINARYOP2", true, false), new TokenCheckTemplate("VAL", true, false)});
    output = new Token("VAL");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //VAL binaryOp1 VAL->VAL
    inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("VAL", true, false), new TokenCheckTemplate("BINARYOP1", true, false), new TokenCheckTemplate("VAL", true, false)});
    output = new Token("VAL");
    rule = new ParserRule(inputs, output);
    Parser::grammarRules.push_back(rule);

    //id -> VAL
    // inputs = new std::vector<TokenCheckTemplate*>({new TokenCheckTemplate("ID", true, false)});
    // output = new Token("VAL");
    // rule = new ParserRule(inputs, output);
    // Parser::grammarRules.push_back(rule);
}

Token* Parser::parse(std::list<Token*> tokens){
    //clear the parse stack
    std::list<Token*> parseStack;

    auto nextTokenIterator = tokens.begin();
    //while not out of bounds
    while (true){
        // for(auto i : parseStack) std::cout << i->contents << "\n";
        //try to go through the stack and reduce

        //get the lookahead token
        Token* lookAheadToken;
        //if there is a next token, add it
        if(nextTokenIterator != tokens.end()) {
            lookAheadToken = *nextTokenIterator;
        }else{
            lookAheadToken = nullToken;
        }
        bool hasBeenReduced = reduce(parseStack, lookAheadToken);

        if(hasBeenReduced) {
            continue;
        }else{
            //shift
            if(nextTokenIterator != tokens.end()){
                parseStack.push_back(*nextTokenIterator);
                nextTokenIterator++;
            }else if(parseStack.size() == 1){
                break;
            }else{
                throw std::runtime_error("Can not parse the expression");
            }
        }
    }

    return *parseStack.begin();
}

bool Parser::reduce(std::list<Token*>& parseStack, Token* nextToken){

    //try all rules and find the longest one that works
    for(auto grammarRule : grammarRules){
        //loop through the possible starting points
        //index of the first token to check
        int index = 0;
        for(auto i = parseStack.begin(); i != parseStack.end(); i++){
            bool hasRuleWorked = true; 

            //if there is a lookahead, check it
            if(grammarRule->isUsingLookAhead){
                bool hasLookAheadWorked = false;
                //all the possible lookaheads
                for(int lookAheadIndex = 0; lookAheadIndex < grammarRule->lookAhead->size(); lookAheadIndex++){
                    //check the one after the end
                    Token* lookAheadToken = smartLookAhead(parseStack, nextToken, std::next(i, grammarRule->inputTokens->size() + 1));
                    if(grammarRule->lookAhead->at(lookAheadIndex)->testToken(lookAheadToken)){
                        hasLookAheadWorked = true;
                        break;
                    }
                }
                if(!hasLookAheadWorked) {
                    continue;
                }
            }
            for(int grammarRuleTokenIndex = 0; grammarRuleTokenIndex < grammarRule->inputTokens->size(); grammarRuleTokenIndex++){
                TokenCheckTemplate* ruleToken = grammarRule->inputTokens->at(grammarRuleTokenIndex);

                //if the rule reaches outside the stack
                if(index + grammarRuleTokenIndex >= parseStack.size()){
                    hasRuleWorked = false;
                    break;
                }

                bool tokenTestResult = ruleToken->testToken(*std::next(i, grammarRuleTokenIndex));
                if(!tokenTestResult) {
                    
                    hasRuleWorked = false;
                    break;
                }
            }


            if(hasRuleWorked){
                //apply reduction

                //check if it is a shift token
                if(shiftTokenCheckTemplate->testToken(grammarRule->outputToken)){
                    //if can be shifted, shift, or otherwise, do nothing
                    if(nextToken->type != TokenTypes::NullToken) return false;
                }else{
                    auto endOfDeletion = std::next(i, grammarRule->inputTokens->size());

                    std::vector<Token*> replacedTokens;
                    //fill the replaced tokens
                    for(auto j = i; j != endOfDeletion; j++) replacedTokens.push_back(*j);

                    //create a new token
                    auto* newToken = new Token(grammarRule->outputToken->contents, grammarRule->outputToken->type);
                    newToken->setChildren(replacedTokens);

                    //insert first to get rid of referencing problems
                    parseStack.insert(i, newToken);
                    parseStack.erase(i, endOfDeletion);

                    return true;
                }
            }

            index++;
        }
    }

    return false;
}