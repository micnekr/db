#include "FunctionComponent.h"

using namespace CustomClasses;

FunctionComponent* FunctionComponent::setValue(){
    throw std::runtime_error("This operation is not supported");
}

void FunctionComponent::operator+(const FunctionComponent& other){
    throw std::runtime_error("This operation is not supported");
}
void FunctionComponent::operator-(const FunctionComponent& other){
    throw std::runtime_error("This operation is not supported");
}
void FunctionComponent::operator*(const FunctionComponent& other){
    throw std::runtime_error("This operation is not supported");
}
void FunctionComponent::operator/(const FunctionComponent& other){
    throw std::runtime_error("This operation is not supported");
}

std::string FunctionComponent::toString(bool toJson) {
    return toString();
}
