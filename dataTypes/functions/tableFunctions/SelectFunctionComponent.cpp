#include "SelectFunctionComponent.h"

using namespace CustomClasses;

SelectFunctionComponent::SelectFunctionComponent(){

}

Component* SelectFunctionComponent::call(ArrayComponent* args){
    std::cout << "Params for the select function:\n" << args->toString() << "\n";
    return new StringComponent("Running select");
}

std::string SelectFunctionComponent::toString(){
    return "built-in function(select)";
}