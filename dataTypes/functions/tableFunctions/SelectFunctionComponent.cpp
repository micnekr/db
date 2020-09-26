#include "SelectFunctionComponent.h"

using namespace CustomClasses;

SelectFunctionComponent::SelectFunctionComponent(){

}

Component* SelectFunctionComponent::call(Component* args[]){
    return new StringComponent("Running select");
}

std::string SelectFunctionComponent::toString(){
    return "Function<select>";
}