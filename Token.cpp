#include "Token.h"

using namespace CustomClasses;

Token::Token(std::string _contents, TokenTypes _type){
    std::cout << "create token;\n";
    children = std::vector<Token*>();
    contents = _contents;
    type = _type;
}

Token::Token(std::string _contents){
    std::cout << "create token;\n";
    children = std::vector<Token*>();
    contents = _contents;
    type = GrammarSymbol;
}

void Token::addChild(Token* child){
    children.push_back(child);
}

void Token::setChildren(std::vector<Token*> _children){
    children = _children;
}

std::string Token::print(int identation) const {
    std::string out;
    for(int i = 0; i < identation; i++) out += "|  ";

    out += "|>--";
    out += contents + std::string(" Type number ") + std::to_string(type) + std::string("\n");

    for(int i = 0; i < children.size(); i++) out += children.at(i)->print(identation + 1);
    return out;
}

std::ostream& operator<<(std::ostream &strm, const CustomClasses::Token &token) {
    return strm << token.print(0);
}

Token::~Token(){
    //delete children
    for(int i = 0; i < children.size(); i++) delete children.at(i);
    std::cout << "destroyed a token\n";
}