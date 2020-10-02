#include "SelectFunctionComponent.h"

using namespace CustomClasses;

SelectFunctionComponent::SelectFunctionComponent(){

}

Component* SelectFunctionComponent::call(ArrayComponent* args){
    return new StringComponent("Running select");
}

std::string SelectFunctionComponent::toString(){
    return "select";
}