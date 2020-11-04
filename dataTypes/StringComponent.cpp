#include "StringComponent.h"

using namespace CustomClasses;

StringComponent::StringComponent(std::string _value){
    value = _value;
}

StringComponent* StringComponent::setValue(std::string _value){
    value = _value;
    return this;
}

std::string StringComponent::toString(){
    return value;
}

Component* StringComponent::operator+(const Component& other){
    //if not a string, throw an error
    const StringComponent* stringComponentPtr = dynamic_cast<const StringComponent*>(&other);
    if(stringComponentPtr == nullptr) throw std::runtime_error("This operation is not supported");

    StringComponent* out = new StringComponent(this->value + stringComponentPtr->value);

    return out;
}

uint32_t StringComponent::getId(){
    if(value.size() == 0) return 0;
    int hash = 0;
    for(int i = 0; i < value.size(); i++){
        hash = hash * 31 + value.at(i);
    }
    return hash;
    // return "";
}