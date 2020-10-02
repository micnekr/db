#include "Connection.h"

using namespace CustomClasses;

Connection::Connection(std::vector<CustomClasses::DataBase *> *_dataBases, int _selectedDataBaseIndex)
{
    selectedDataBaseIndex = _selectedDataBaseIndex;
    dataBases = _dataBases;
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
                IdComponent* out =  new IdComponent(token->children.at(0)->contents);
                if(parent == nullptr){
                    Component* resolved = resolveTopLevelId(out->name);
                    if(resolved == nullptr) return new NullComponent();
                    else return resolved;
                }else return out;
            }

            //if it is id.id
            else if(token->children.at(1)->contents == "DOT"){
                //expand the leftward ones
                //the leftward ones will always lead to the global id
                //the right ones will always be an ID containing an id name
                Component* leftComponent = computeQuery(token->children.at(0), parent);
                std::string rightIdName = token->children.at(2)->children.at(0)->contents;

                std::cout << "finding children against " + rightIdName + "\n";
                //check if the right one is a child of the left one
                for(int i = 0; i < leftComponent->children.size(); i++){
                    std::cout << leftComponent->children.at(i)->toString() << "\n";
                    if(leftComponent->children.at(i)->toString() == rightIdName){
                        return leftComponent->children.at(i);
                    }
                }

                //not found
                std::cout << "not found\n";
                return new NullComponent();
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
                        params = (new ArrayComponent())->addValue(rawParams);
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
            if(dynamic_cast<ArrayComponent*>(leftResult) == nullptr) parentArray->addValue(leftResult);

            //then add right
            parentArray->addValue(computeQuery(token->children.at(2), parentArray));
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

Component* Connection::resolveTopLevelId(std::string varName){
    std::cout << "resolving " << varName << "\n";
    //try to recognise it
    DataBase *currentDataBase = dataBases->at(0);
    std::vector<CustomClasses::Component *> currentTables = currentDataBase->children;
    //check if it is a name of a current table
    for (int i = 0; i < currentTables.size(); i++)
    {
        std::cout << "table'" << currentTables.at(i)->toString() << "'\n";
        if (currentTables.at(i)->toString() == varName)
        {
            std::cout << "resolved table\n";
            return currentTables.at(i);
        }
    }

    //check all the database names
    for (int i = 0; i < dataBases->size(); i++)
    {
        std::cout << "db'" << dataBases->at(i)->toString() << "'\n";
        if (dataBases->at(i)->name == varName)
        {
            std::cout << "resolved db\n";
            return dataBases->at(i);
        }
    }
    return new NullComponent();
}

void Connection::execute(Token *token)
{
    std::string result = computeQuery(token)->toString();
    std::cout << "result:\n" << result;
}