#include "Lexer.h"

using namespace CustomClasses;

char whitespaceChars [] = {' ', '\n', '\t'};

bool safelyCheckChars(int, std::string, std::string);
TokenTypes getTokenType(char, int, std::string);

//TODO: escape characters
//TODO: alert unescaped comments, strings
std::vector<Token*> Lexer::tokenize(std::string in){
    std::vector<Token*> out;
    TokenTypes currentState = NoToken;
    std::string currentToken = "";

    char stringChar = '_';

    //go through the string character by character
    for(int i = 0; i < in.length(); i++){
        char currentChar = in.at(i);

        if(currentState == Comment){
            if(safelyCheckChars(i - 1, in, "*/")){
                std::cout << "comment" << currentChar << "\n";
                currentState = NoToken;
            }
            continue;
        }

        //TODO: refactor

        //TODO: stop tokenes more precisely, e.g. abcd+

        //if the current token is ended
        if(Lexer::isWhitespaceChar(currentChar) && currentState != String && currentState != Comment){
            // don't create many empty tokens
            if(currentState != NoToken){
                out.push_back(new Token(currentToken, currentState));
                currentToken = "";
                currentState = NoToken;
            }

            continue;
        }

        startTokenTypeTest:
        TokenTypes charTokenType = getTokenType(currentChar, i, in);
        //start of a new token
        if(currentState == NoToken){
            currentState = charTokenType;

            switch (currentState)
            {
            case String:
                stringChar = currentChar;
                continue;
                break;

            case RoundBracket:
                currentToken += currentChar;
                out.push_back(new Token(currentToken, RoundBracket));
                currentToken = "";
                currentState = NoToken;
                continue;
                break;

            case Comment:
                continue;

            default:
                break;
            }
        //closing strings
        }else if(currentState == String && currentChar == stringChar){
            out.push_back(new Token(currentToken, currentState));
            currentToken = "";
            currentState = NoToken;
            continue;
        //if an unexpected char for a token type, go back to the top and check its type
        //accept numbers with a decimal part
        }else if(charTokenType != currentState && !(currentState == Number && currentChar == '.') && currentState != String){
            out.push_back(new Token(currentToken, currentState));
            currentToken = "";
            currentState = NoToken;
            //check the new token, will alway go to the new token branch
            goto startTokenTypeTest;
        }

        currentToken += currentChar;
    }

    if(currentToken != "") out.push_back(new Token(currentToken, currentState));

    return out;
}

bool Lexer::isWhitespaceChar(char character){
    for(int i = 0; i < (sizeof(whitespaceChars)/sizeof(*whitespaceChars)); i++){
        if(whitespaceChars[i] == character) return true;
    }
    return false;
}

bool Lexer::isOperatorChar(char character){
    return (character == '+') || (character == '-') ||  (character == '*') || (character == '/') || (character == '=') || (character == '<') || (character == '>')  || (character == '!') || (character == '.' || (character == ','));
}

TokenTypes getTokenType(char currentChar, int i, std::string in){
    if(isalpha(currentChar)){
        return Identifer;
    }else if (isdigit(currentChar)){
        return Number;
    }else if (currentChar == '"' || currentChar == '\''){
        return String;
    }else if (safelyCheckChars(i, in, "/*")){
        return Comment;
    }else if (Lexer::isOperatorChar(currentChar)){
        return OperatorSymbols;
    }else if(currentChar == '(' || currentChar == ')'){
        return RoundBracket;
    }

    //not sure what it is
    return NoToken;
}

bool safelyCheckChars(int index, std::string in, std::string pattern){
    const int inLength = in.length();
    for(int i = 0; i < pattern.length(); i++){
        if(index + i >= inLength || i < 0) return false;
        if(in[index + i] != pattern[i]) return false;
    }
    return true;
}