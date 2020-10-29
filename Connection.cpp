#include "Connection.h"

using namespace CustomClasses;

Connection::Connection(std::vector<DataBase*> *_dataBases, DataBase* _selectedDataBase, FileAccess* _fileAccess, IdComponent* _globalIdComponent)
{
    selectedDataBase = _selectedDataBase;
    dataBases = _dataBases;
    fileAccess = _fileAccess;
    globalIdComponent = _globalIdComponent;
}

Component* Connection::computeQuery(Token *token, Component *parent = nullptr)
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

        //if a more high-level symbol, continue
    case TokenTypes::GrammarSymbol:

        //maths expressions
        if(token->contents == "VAL"){
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
            std::cout << "new id\n";

            //if a single token, make the idcomponent based on the child's name
            if(token->children.size() == 1) {
                IdComponent* out;
                if(parent == nullptr){
                    std::string key = token->children.at(0)->contents;
                    //try to find it as a child in the global id component
                    //if not found
                    if(globalIdComponent->children.find(key) == globalIdComponent->children.end()) {
                        return new NullComponent();
                    }else{
                        return globalIdComponent->children[key];
                    }
                }else {
                    std::cout << "has a parent for some reason\n";
                    return out;
                }
            }

            //if it is id.id
            else if(token->children.at(1)->contents == "DOT"){
                //expand the leftward ones
                //the leftward ones will always lead to the global id
                //the right ones will always be an ID containing an id name
                Component* leftComponent = computeQuery(token->children.at(0), parent);
                std::string rightIdName = token->children.at(2)->children.at(0)->contents;
                std::cout << "finding children called '" + rightIdName + "'\n";
                //check if the right one is a child of the left one
                bool hasFound = leftComponent->children.find(rightIdName) != leftComponent->children.end();
                if(!hasFound){
                    //not found
                    std::cout << "not found\n";
                    return new NullComponent();
                }else{
                    return leftComponent->children[rightIdName];
                }
            //calling functions
            }else if (token->children.at(1)->contents == "BRACKET_EXPRESSION"){
                std::cout << "calling\n";
                // if no parameters, call with an empty array of parameters
                ArrayComponent* params;
                if(token->children.at(1)->children.size() == 2) params = new ArrayComponent();
                //both multiple arguments and bracketed expressions
                else {
                    std::cout << "non-empty params\n";
                    Component* rawParams = computeQuery(token->children.at(1));

                    ArrayComponent* castedParams = dynamic_cast<ArrayComponent*>(rawParams);

                    //if it is not an array, push it into an array
                    if(castedParams == nullptr){
                        params = new ArrayComponent();
                        params->addChild(rawParams);
                    }else params = castedParams;
                }

                std::cout << "params:\n";
                std::cout << params->toString() << "\n";

                return computeQuery(token->children.at(0))->call(params);
            }

        //unknown
        }else if(token->contents == "ARRAY_PART"){
            //if the parent is an array
            ArrayComponent* parentArray = dynamic_cast<ArrayComponent*>(parent);
            if(parentArray == nullptr) parentArray = new ArrayComponent();

            //add the left first
            Component* leftResult = computeQuery(token->children.at(0), parentArray);

            //if the left result is not a part of the array, add it
            if(dynamic_cast<ArrayComponent*>(leftResult) == nullptr) parentArray->addChild(leftResult);

            //then add right
            parentArray->addChild(computeQuery(token->children.at(2), parentArray));
            return parentArray;
        }else if(token->contents == "BRACKET_EXPRESSION"){

            //return what is inside
            return computeQuery(token->children.at(1));
        }else{
            std::cout << "not recognised\n";
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
    std::string result = computeQuery(token)->toString();
    std::cout << "result:\n" << result << "\n";
}