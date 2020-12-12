#include "SelectFunctionComponent.h"

using namespace CustomClasses;

SelectFunctionComponent::SelectFunctionComponent() = default;

Component* SelectFunctionComponent::call(ArrayComponent* args){
    std::cout << "calling select\n";

    //TODO: check arg length
    //TODO: make the functions accept a fixed number of params?
    std::cout << "Params for the select function:\n" << args->toString() << "\n";
    Component* key = args->children.at("0");

    auto* database = dynamic_cast<DataBase*>(parent->parent);

    if(database == nullptr) throw std::runtime_error("The ancestry of the selectFunctionComponent is incorrect");

    Component* result = database->search(key);

    auto* out = new ArrayComponent();

    //if not found
    if(result == nullptr) {
        std::cout << "not found\n";
        //return empty
        return out;
    }

    if(dynamic_cast<NumberComponent*>(result) != nullptr) std::cout << "number\n";

    std::cout << "result: " << result->toString() << "\n";

    out->addChild(result);

    return out;
}

std::string SelectFunctionComponent::toString(){
    return "built-in function(select)";
}
