//#define _WIN32_WINNT 0x0601
//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif

//#include "dep/restinio/restinio/all.hpp"
#include "CustomClasses.h"
#include <list>
#include <iostream>

int main() {
    try {
        //global IdComponent
        auto *globalIdComponent = new CustomClasses::IdComponent();

        auto *dataBases = new std::vector<CustomClasses::DataBase *>();

        std::cout << "new database\n";

        auto *settingsDatabase = new CustomClasses::DataBase("testDb", "db.pm", "db.sm", 10000, 10000);

        dataBases->push_back(settingsDatabase);
        globalIdComponent->setChild(settingsDatabase->name, settingsDatabase);

        std::cout << "a new table\n";


        settingsDatabase->createTable("testTable");
//        std::cout << "Store" << "\n";
//        settingsDatabase->store(new CustomClasses::StringComponent("I"),
//                                new CustomClasses::StringComponent("ABCDABCD"));
//        settingsDatabase->store(new CustomClasses::StringComponent("Index1"),
//                                new CustomClasses::StringComponent("DCBADCBA"));
//        settingsDatabase->store(new CustomClasses::StringComponent("Index2"),
//                                new CustomClasses::StringComponent("TestTest"));
//        std::cout << "Search" << "\n";
//        CustomClasses::Component *retrieved = settingsDatabase->search(new CustomClasses::StringComponent("Index1"));
//        std::cout << "Finished search, ptr: " << int(retrieved) << "\n";
//        std::cout << retrieved->toString() << "\n";
        //language functionality

        //parser
        CustomClasses::Parser::init();

        std::string languageInput;
        std::getline(std::cin, languageInput);

        std::cout << "Tokenising" << "\n";
        std::list<CustomClasses::Token *> tokens = CustomClasses::Lexer::tokenize(languageInput);

        std::cout << "Tokenised" << "\n";

        for (auto const &i : tokens) {
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
    } catch (std::string &ex) {
        std::cout << "\n\n" << ex << "\n";
        int waitForInput;
        std::cin >> waitForInput;
    } catch (const char *ex) {
        std::cerr << "\n\n" << ex << "\n";
        int waitForInput;
        std::cin >> waitForInput;
    }
}