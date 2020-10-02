#include "Parser.h"

using namespace CustomClasses;

std::vector<ParserRule*> Parser::grammarRules;
Token* nullToken;
TokenCheckTemplate* shiftTokenCheckTemplate = new TokenCheckTemplate("SHIFT", true, false);

template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n) {
   auto first = v.begin() + m;
   auto last = v.begin() + n;
   std::vector<T> vector(first, last);
   return vector;
}

void Parser::init(){
    nullToken = new Token("", TokenTypes::NullToken);
    Parser::grammarRules.clear();

    ParserRule* rule;

    std::vector<TokenCheckTemplate*>* inputs = new std::vector<TokenCheckTemplate*>();
    Token* output;
    std::vector<TokenCheckTemplate*>* lookAhead = new std::vector<TokenCheckTemplate*>();

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

Token* Parser::parse(std::vector<Token*> tokens){
    //clear the parse stack
    std::vector<Token*> parseStack;

    int tokenIndex = 0;
    //while not out of bounds
    while (true){
        std::cout << "new round\n";
        for(int i = 0; i < parseStack.size(); i++) std::cout << parseStack.at(i)->contents << "\n";
        //try to go through the stack and reduce
        bool hasBeenReduced = false;

        Token* lookAheadToken;
        if(tokenIndex < tokens.size()) {
            lookAheadToken = tokens.at(tokenIndex);
        }else{
            lookAheadToken = nullToken;
        }
        hasBeenReduced = reduce(parseStack, lookAheadToken);

        if(hasBeenReduced) {
            continue;
        }

        //shift
        if(!hasBeenReduced){
            if(tokenIndex < tokens.size()){
                parseStack.push_back(tokens.at(tokenIndex));
                tokenIndex++;
            }else if(parseStack.size() == 1){
                break;
            }else{
                throw std::runtime_error("Can not parse the expression");
            }
        }
    }

    return parseStack.at(0);
}

bool Parser::reduce(std::vector<Token*>& parseStack, Token* nextToken){
    std::vector<Token*> lookAheadStack = parseStack;

    lookAheadStack.push_back(nextToken);

    //try all rules and find the longest one that works
    for(int grammarRuleIndex = 0; grammarRuleIndex < grammarRules.size(); grammarRuleIndex++){
        ParserRule* grammarRule = grammarRules.at(grammarRuleIndex);

        for(int index = 0; index < parseStack.size(); index++){
            bool hasRuleWorked = true; 

            //if there is a lookahead, check it
            if(grammarRule->isUsingLookAhead){
                bool hasLookAheadWorked = false;
                for(int lookAheadIndex = 0; lookAheadIndex < grammarRule->lookAhead->size(); lookAheadIndex++){
                    //check the one after the end
                    Token* lookAheadToken = lookAheadStack.at(index + grammarRule->inputTokens->size());
                    if(grammarRule->lookAhead->at(lookAheadIndex)->testToken(lookAheadToken)){
                        hasLookAheadWorked = true;
                        break;
                    }
                }
                if(!hasLookAheadWorked) continue;
            }
            for(int grammarRuleTokenIndex = 0; grammarRuleTokenIndex < grammarRule->inputTokens->size(); grammarRuleTokenIndex++){
                TokenCheckTemplate* ruleToken = grammarRule->inputTokens->at(grammarRuleTokenIndex);

                //if the rule reaches outside the stack
                if(index + grammarRuleTokenIndex >= parseStack.size()){
                    hasRuleWorked = false;
                    break;
                }

                bool tokenTestResult = ruleToken->testToken(parseStack.at(index + grammarRuleTokenIndex));
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
                    std::vector<Token*> newStack;
                    newStack = slice(parseStack, 0, index);


                    std::vector<Token*> replacedTokens = slice(parseStack, index, index + grammarRule->inputTokens->size());

                    //create a new token
                    Token* newToken = new Token(grammarRule->outputToken->contents, grammarRule->outputToken->type);
                    newToken->setChildren(replacedTokens);

                    newStack.push_back(newToken);
                    newStack.insert(newStack.end(), parseStack.begin() + index + grammarRule->inputTokens->size(), parseStack.end());

                    parseStack = newStack;
                    return true;
                }
            }
        }
    }

    return false;;
}