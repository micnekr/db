#include "CustomClasses.h"
#include <list>
#include <iostream>
int main()
{
    try {
        //global IdComponent
        CustomClasses::IdComponent *globalIdComponent = new CustomClasses::IdComponent();

        std::vector<CustomClasses::DataBase *> *dataBases = new std::vector<CustomClasses::DataBase *>();

        std::cout << "new database\n";

        CustomClasses::DataBase *settingsDatabase = new CustomClasses::DataBase("testDb", "db.pm", "db.sm", 100, 100);

        dataBases->push_back(settingsDatabase);
        globalIdComponent->setChild(settingsDatabase->name, settingsDatabase);

        std::cout << "a new table\n";


        settingsDatabase->createTable("testTable");
        auto* testIndex = new std::vector<unsigned char>();
//        auto* testData = new std::vector<unsigned char>();
        testIndex->push_back(3);
//        testData->push_back(0x43);
//        settingsDatabase->storePrimaryMap(testIndex, testData);
//        settingsDatabase->storePrimaryAndSecondaryMap(testIndex, new CustomClasses::StringComponent("ABCDABCD"));
//        settingsDatabase->storePrimaryAndSecondaryMap(testIndex, new CustomClasses::StringComponent("DCBADCBA"));
//        settingsDatabase->storePrimaryAndSecondaryMap(testIndex, new CustomClasses::StringComponent("TestTest"));
        CustomClasses::Component* retrieved = settingsDatabase->searchPrimaryAndSecondaryMap(testIndex);
        std::cout << retrieved->toString() << "\n";

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

        CustomClasses::Connection connection(dataBases, settingsDatabase, globalIdComponent);

        std::cout << "executing...\n";

        connection.execute(token);

        delete token;
        delete settingsDatabase;

        std::string waitString;
        std::cin >> waitString;
        return 0;
    }catch(std::string ex){
        std::cerr << "\n\n" << ex << "\n";
        int waitForInput;
        std::cin >> waitForInput;
    }catch(const char* ex){
        std::cerr << "\n\n" << ex << "\n";
        int waitForInput;
        std::cin >> waitForInput;
    }
}