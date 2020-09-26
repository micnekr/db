#include "Connection.h"

using namespace CustomClasses;

Connection::Connection(std::vector<CustomClasses::DataBase *> *_dataBases, int _selectedDataBaseIndex)
{
    selectedDataBaseIndex = _selectedDataBaseIndex;
    dataBases = _dataBases;
}

//TODO: a function to find a component by id name(not parent)
//TODO: component children - inheritance

Component* Connection::computeQuery(Token *token, Component *parent = NULL)
{
    std::cout << token->contents << "\n";

    switch (token->type)
    {
    case TokenTypes::Number:
        //if a number, return the number component
        return new  NumberComponent(std::stod(token->contents));
        break;
    case TokenTypes::String:
        //if string, return the string component
        return new  StringComponent(token->contents);
    case TokenTypes::GrammarSymbol:

        //maths expressions
        if(token->contents == "BRACKET_EXPRESSION"){
            return computeQuery(token->children.at(1), parent);
        }else if(token->contents == "VAL"){
            NumberComponent* numberComponent = new  NumberComponent(0);

            //pass upwards
            if (token->children.size() == 1)
            {
                return computeQuery(token->children.at(0), numberComponent);
            }
            else if (token->children.size() == 3)
            {
                std::string op = token->children.at(1)->children.at(0)->contents;
                // recursively get operands and cast them
                Component* operand1 = computeQuery(token->children.at(0), numberComponent);
                Component* operand2 = computeQuery(token->children.at(2), numberComponent);

                // if can not be cast, throw an error
                if(operand1 == nullptr || operand2 == nullptr){
                    throw std::runtime_error("Not a math value used with a math operator");
                }

                if (op == "-")
                    return *operand1 - *operand2;
                if (op == "+")
                    return *operand1 + *operand2;
                if (op == "*")
                    return *operand1 * *operand2;
                if (op == "/")
                    return *operand1 / *operand2;
                throw std::runtime_error("Unknown operator");
            }
            else
            {
                throw std::runtime_error("Unknown maths expression");
            }
        //if an id
        }else if (token->contents == "ID"){

            //TODO: a list/map of all declared ids; per connection? and combined?
            //try to recognise it
            DataBase *currentDataBase = dataBases->at(0);
            std::vector<CustomClasses::Component *> currentTables = currentDataBase->children;
            //check if it is a name of a current table
            for (int i = 0; i < currentTables.size(); i++)
            {
                if (currentTables.at(i)->toString() == token->contents)
                {
                    return currentTables.at(i);
                }
            }

            //check all the database names
            for (int i = 0; i < dataBases->size(); i++)
            {
                if (dataBases->at(i)->name == token->contents)
                {
                    return dataBases->at(i);
                }
            }
        //unknown
        }else{
            throw std::runtime_error("Unknown token type");
        }
        break;
    
    default:
        break;
    }

    throw std::runtime_error("Can not find action for the token");
    return 0;
}

void Connection::execute(Token *token)
{
    std::cout << "result:\n";
    std::cout << computeQuery(token)->toString();
}