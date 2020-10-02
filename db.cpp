#include "CustomClasses.h"
#include <list>
#include <iostream>

int main () {
    CustomClasses::Parser::init();

    std::string languageInput;
    std::getline(std::cin, languageInput);

    std::list<CustomClasses::Token*> tokens = CustomClasses::Lexer::tokenize(languageInput);

    for(auto const& i : tokens){
        std::cout << "'"<< i->contents << "'" << i->type << "\n";
    }

    CustomClasses::Token* token = CustomClasses::Parser::parse(tokens);

    std::vector<CustomClasses::DataBase*>* dataBases = new std::vector<CustomClasses::DataBase*>();

    std::cout << "new database\n";


    CustomClasses::DataBase* settingsDatabase = new CustomClasses::DataBase("testDb");

    dataBases->push_back(settingsDatabase);

    std::cout << "a new table\n";

    settingsDatabase->createTable("testTable");

    std::cout << *token <<"\n";

    std::cout << "new connection\n";

    CustomClasses::Connection connection(dataBases, 0);

    std::cout << "executing...\n";

    connection.execute(token);

    delete token;
    delete settingsDatabase;

    std::string testString;
    std::cin >> testString; 
    return 0;
}