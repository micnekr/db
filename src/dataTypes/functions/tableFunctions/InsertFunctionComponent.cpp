//
// Created by misha on 12/12/2020.
//

#include "InsertFunctionComponent.h"
#include "../../../DataBase.h"

std::string CustomClasses::InsertFunctionComponent::toString() {
    return "built-in function(insert)";
}

CustomClasses::Component *CustomClasses::InsertFunctionComponent::call(CustomClasses::ArrayComponent *args) {
    std::cout << "calling insert\n";

    //TODO: check arg length
    //TODO: make the functions accept a fixed number of params?
    std::cout << "Params for the insert function:\n" << args->toString() << "\n";
    Component* key = args->children.at("0");
    Component* value = args->children.at("1");

    auto* database = dynamic_cast<DataBase*>(parent->parent);

    if(database == nullptr) throw std::runtime_error("The ancestry of the insertFunctionComponent is incorrect");

    database->store(key, value);

    return new NullComponent();
}
