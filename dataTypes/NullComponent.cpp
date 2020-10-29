#include "NullComponent.h"

using namespace CustomClasses;

const std::size_t NullComponent::hashValue = std::hash<std::string>{}("null");

NullComponent::NullComponent(){}

std::string NullComponent::toString(){
    return "Null";
}