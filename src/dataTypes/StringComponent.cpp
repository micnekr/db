#include "StringComponent.h"

#include <utility>

using namespace CustomClasses;

StringComponent::StringComponent(std::string _value) {
    value = std::move(_value);
}

StringComponent *StringComponent::setValue(std::string _value) {
    value = std::move(_value);
    return this;
}

std::string StringComponent::toString() {
    return '"' + value + '"';
}

Component *StringComponent::operator+(const Component &other) {
    //if not a string, throw an error
    const auto *stringComponentPtr = dynamic_cast<const StringComponent *>(&other);
    if (stringComponentPtr == nullptr) throw std::runtime_error("This operation is not supported");

    auto *out = new StringComponent(this->value + stringComponentPtr->value);

    return out;
}

uint32_t StringComponent::generateId() {
    if (value.empty()) return 0;
    int hash = 0;
    for (char i : value) {
        hash = hash * 31 + i;
    }
    return hash;
}

std::vector<unsigned char> *StringComponent::serialise() {
    auto *bytes = new std::vector<unsigned char>(value.begin(), value.end());
    return bytes;
}

Component *StringComponent::deserealise(std::vector<unsigned char> *bytes) {

    //convert bytes to a byte array
    const auto byteVectorSize = bytes->size();
    char* unsignedBytes = new char[byteVectorSize];
    std::copy(bytes->begin(), bytes->end(), unsignedBytes);

    //make them signed
    const char *signedBytes = reinterpret_cast< char * >(unsignedBytes);

    //create a string, second argument is length to ensure null chars aren't lost
    value = std::string(signedBytes, bytes->size());
    return this;
}

StringComponent::StringComponent(Component * toConvert) {
    auto* stringComponentPointer = dynamic_cast<StringComponent*>(toConvert);
    if(stringComponentPointer != nullptr){
        value = stringComponentPointer->value;
    }else{
        value = toConvert->toString();
    }
}
