#include "CustomClasses.h"
#include <vector>
#include <iostream>

int main () {
    // std::string languageInput = "SELECT * FROM '123 ABC'        34+32*56 /*test 'commented out*/testTable";
    // std::string languageInput = "2.5*   4+1 * 77";
    std::string languageInput;
    std::getline(std::cin, languageInput);

    std::vector<CustomClasses::Token*> tokens = CustomClasses::Lexer::tokenize(languageInput);

    for(int i = 0; i < tokens.size(); i++){
        std::cout << "'"<< tokens.at(i)->contents << "'" << tokens.at(i)->type << "\n";
    }

    CustomClasses::Parser::init();
    CustomClasses::Token* token = CustomClasses::Parser::parse(tokens);

    std::vector<CustomClasses::DataBase*>* dataBases = new std::vector<CustomClasses::DataBase*>();

    std::cout << "new database\n";


    CustomClasses::DataBase* settings = new CustomClasses::DataBase("testDb");

    dataBases->push_back(settings);

    std::cout << "a new table\n";

    settings->createTable("testTable");

    std::cout << *token <<"\n";

    std::cout << "new connection\n";

    CustomClasses::Connection connection(dataBases, 0);

    std::cout << "executing...\n";

    connection.execute(token);

    //std::cout << testDatabase.print();

    std::string testString;
    std::cin >> testString; 
    return 0;
}