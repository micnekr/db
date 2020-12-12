//
// Created by misha on 11/12/2020.
//

#include "Server.h"
#include "Parser.h"
#include "Lexer.h"

using namespace CustomClasses;
using namespace std;

Server::Server(std::vector<DataBase *> *_dataBases, DataBase *_selectedDataBase, IdComponent *_globalIdComponent) {
    //start the server
    m_listener = http::experimental::listener::http_listener(L"http://localhost:9000");
    m_listener.open().wait();

    m_listener.support(methods::POST, std::bind(&Server::handlePost, this, std::placeholders::_1));

    CustomClasses::Parser::init();
    connection = new Connection(_dataBases, _selectedDataBase, _globalIdComponent);

    std::string languageInput;
}

web::json::value stringToJson(std::string const &input) {
    utility::stringstream_t s;

    s << utility::conversions::to_utf16string(input);
    web::json::value ret = json::value::parse(s);
    return ret;
}

void handle_request(
        http_request request,
        function<void(json::value const &, json::value &, bool &)> action) {
    auto answer = json::value::object();
    bool hasReplied = false;

    request
            .extract_json(true)
            .then([&answer, &action, &hasReplied](pplx::task<json::value> task) {
                try {
                    std::cout << "Ready to decode\n";
                    auto const &jvalue = task.get();
                    std::cout << "Decoded\n";
//                    display_json(jvalue, L"R: ");
                    if (!jvalue.is_null()) {
                        std::cout << "not null\n";
                        action(jvalue, answer, hasReplied);
                    } else {
                        std::cout << "null \n";
                    }
                }
                catch (http_exception const &e) {
                    std::cout << "Error\n";
                    wcout << e.what() << endl;
                } catch(std::exception& ex){
                    std::cout << "Error - exception\n";
                    wcout << ex.what() << endl;
                } catch(...){std::cout << "Error\n";}
            })
            .wait();

    std::cout << "Has replied " << hasReplied << "\n";
    if(!hasReplied) request.reply(status_codes::OK, answer);
}

void Server::handlePost(http_request request) {
    std::cout << "post request\n";

    const auto HeaderString = request.to_string();
    std::wcout << "header" << HeaderString.c_str() << std::endl;

    std::cout << "Start extraction\n";

    handle_request(
            request,
            [this, &request](json::value const &jvalue, json::value &answer, bool &hasReplied) {
                if(jvalue.is_null() || !jvalue.is_array() || jvalue.as_array().size() == 0){
                    std::cout << "icorrect form - not an array\n";
                    hasReplied = true;
                    request.reply(status_codes::BadRequest);
                    return;
                }
                std::cout << "is array " << jvalue.is_array() << "\n";

                auto params = jvalue.as_array();
                std::string query = utility::conversions::to_utf8string(params.at(0).as_string());

                std::cout << "query: '" << query << "'\n";

                std::cout << "Tokenising" << "\n";
                std::list<CustomClasses::Token *> tokens = CustomClasses::Lexer::tokenize(query);

                std::cout << "Tokenised" << "\n";

                for (auto const &i : tokens) {
                    std::cout << "'" << i->contents << "'" << i->type << "\n";
                }

                std::cout << "Parsing\n";

                CustomClasses::Token *token;
                try {
                    token = CustomClasses::Parser::parse(tokens);
                }catch(...){
                    //can not parse
                    std::cout << "Can not parse\n";
                    hasReplied = true;
                    request.reply(status_codes::BadRequest);
                    return;
                }

                std::cout << *token << "\n";

                std::cout << "executing...\n";

                Component* result = connection->execute(token);

                delete token;

                std::cout << "result: '" << result->toString(true) << "'\n";

                answer[L"results"] = stringToJson(result->toString(true));

//                for (auto const & e : jvalue.as_array())
//                {
//                    if (e.is_string())
//                    {
//                        auto key = e.as_string();
//                        std::wcout << key << "\n";
//                    }else{
//                        std::cout << "not a string\n";
//                    }
//                }
            });

//    auto answer = json::value::object();
//    json::value params;
//
//    json::value temp;
//    std::cout << "preparing to extract\n";
//    request.extract_json(true)       //extracts the request content into a json
//            .then([&temp](pplx::task<json::value> task)
//                  {
//                try{
//                    temp = task.get();
//                    std::cout << "Is empty? " << temp.is_null() << "\n";
//                }catch (const std::exception& ex) {
//                    std::cout << "Exception std" << ex.what() << "\n";
//                }
//                catch (const std::string& ex) {
//                    std::cout << "Exception " << ex << "\n";
//                }
//                catch(...){
//                    std::cout << "exception\n";
//                }
//                  })
//            .wait();
//    std::wcout << temp.as_string() << " - params\n";

//    request
//            .extract_json()
//            .then([&params](pplx::task<json::value> task) {
//                try {
//                    params = task.get();
//                    if(!params.is_null()){
//                    auto string = params.as_string();
//                    std::wcout << "new value: '" <<  string << "'\n";
//                    }else{
//                        std::cout << "null\n";
//                    }
//                } catch (http_exception const &e)
//                {
//                    std::wcout << e.what() << std::endl;
//                }
//            })
//            .wait();
//            .then([](pplx::task<json::value> task) {
//                try
//                {
//                    json::value jvalue = task.get();
//
//
//                    if (!jvalue.is_null())
//                    {
//                        std::wcout << "new value" << jvalue.as_string() << "\n";
//                    }else{
//                        std::cout << "null\n";
//                    }
//                }
//                catch (http_exception const & e)
//                {
//                    std::wcout << e.what() << std::endl;
//                }
//            })
//            .wait();

//    answer[L"C++"] = json::value::string(U("IS SO HARD"));
//    answer[L"but"] = json::value::string(U("it works somehow"));

//    request.reply(status_codes::OK, answer);
}