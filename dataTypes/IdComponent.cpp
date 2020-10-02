#include "IdComponent.h"

using namespace CustomClasses;

IdComponent::IdComponent(std::string _name){
    name = _name;
}

IdComponent::IdComponent(){
    name = "";
}

IdComponent* IdComponent::setValue(std::string _name){
    name = _name;
    return this;
}

std::string IdComponent::toString(){
    return name;
}