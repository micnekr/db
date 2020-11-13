#include "CustomClasses.h"
#include <list>
#include <iostream>
#include <cstring>

int main()
{
    std::cout << std::hex << ((new CustomClasses::IdComponent())->getId()) << "\n";

    //file access
    CustomClasses::FileAccess *fileAccess = new CustomClasses::FileAccess();

    //global IdComponent
    CustomClasses::IdComponent *globalIdComponent = new CustomClasses::IdComponent();

    std::vector<CustomClasses::DataBase *> *dataBases = new std::vector<CustomClasses::DataBase *>();

    std::cout << "new database\n";

    CustomClasses::DataBase *settingsDatabase = new CustomClasses::DataBase("testDb", "db.pm", "db.sm", 100, 100);

    dataBases->push_back(settingsDatabase);
    globalIdComponent->setChild(settingsDatabase->name, settingsDatabase);

    std::cout << "a new table\n";

    settingsDatabase->createTable("testTable");
    settingsDatabase->store(6, new CustomClasses::StringComponent("ABCD"));

    //language functionality

    //parser
    CustomClasses::Parser::init();

    std::string languageInput;
    std::getline(std::cin, languageInput);

    std::list<CustomClasses::Token *> tokens = CustomClasses::Lexer::tokenize(languageInput);

    for (auto const &i : tokens)
    {
        std::cout << "'" << i->contents << "'" << i->type << "\n";
    }

    CustomClasses::Token *token = CustomClasses::Parser::parse(tokens);

    std::cout << *token << "\n";

    std::cout << "new connection\n";

    CustomClasses::Connection connection(dataBases, settingsDatabase, fileAccess, globalIdComponent);

    std::cout << "executing...\n";

    connection.execute(token);

    delete token;
    delete settingsDatabase;

    std::string testString;
    std::cin >> testString;
    return 0;
}