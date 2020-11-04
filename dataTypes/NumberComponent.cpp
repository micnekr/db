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
    std::string out = std::to_string(value);

    //loop backwards to check for trailing zeros
    for(int i = out.length() - 1; i >= 0; i--){
        if(out[i] != '0' && out[i] != '.') return out.substr(0, i + 1);
    }
    return out;
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

uint32_t NumberComponent::getId(){
    uint64_t valueAsInt;
    std::memcpy(&valueAsInt, &value, sizeof(value));

    uint32_t result = ((valueAsInt << 32) ^ (valueAsInt >> 32));

    return result;
}