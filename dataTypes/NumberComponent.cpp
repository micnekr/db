#include "NumberComponent.h"

using namespace CustomClasses;

NumberComponent::NumberComponent(double _value){
    value = _value;
}

NumberComponent* NumberComponent::setValue(double _value){
    value = _value;
    return this;
}

std::string NumberComponent::toString(){
    return std::to_string(value);
}

Component* NumberComponent::operator+(const Component& other){
    //if not a number, throw an error
    const NumberComponent* numberComponentPtr = dynamic_cast<const NumberComponent*>(&other);
    if(numberComponentPtr == nullptr) throw std::runtime_error("This operation is not supported");

    NumberComponent* out = new NumberComponent(this->value + numberComponentPtr->value);

    return out;
}
Component* NumberComponent::operator-(const Component& other){
    //if not a number, throw an error
    const NumberComponent* numberComponentPtr = dynamic_cast<const NumberComponent*>(&other);
    if(numberComponentPtr == nullptr) throw std::runtime_error("This operation is not supported");

    NumberComponent* out = new NumberComponent(this->value - numberComponentPtr->value);

    return out;
}
Component* NumberComponent::operator*(const Component& other){
    //if not a number, throw an error
    const NumberComponent* numberComponentPtr = dynamic_cast<const NumberComponent*>(&other);
    if(numberComponentPtr == nullptr) throw std::runtime_error("This operation is not supported");

    NumberComponent* out = new NumberComponent(this->value * numberComponentPtr->value);

    return out;
}
Component* NumberComponent::operator/(const Component& other){
    //if not a number, throw an error
    const NumberComponent* numberComponentPtr = dynamic_cast<const NumberComponent*>(&other);
    if(numberComponentPtr == nullptr) throw std::runtime_error("This operation is not supported");

    NumberComponent* out = new NumberComponent(this->value / numberComponentPtr->value);

    return out;
}