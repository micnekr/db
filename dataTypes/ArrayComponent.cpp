#include "ArrayComponent.h"

using namespace CustomClasses;

ArrayComponent* ArrayComponent::addValue(Component* _value){
    value.push_back(_value);
    return this;
}

std::string ArrayComponent::toString(){
    std::string out = "[";
    for(int i = 0; i < value.size(); i++) {
        out += value.at(i)->toString();
        if(i != value.size() - 1) out += ", ";
    }
    return out + "]";
}