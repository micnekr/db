#include "NullComponent.h"

using namespace CustomClasses;

const std::size_t NullComponent::hashValue = std::hash<std::string>{}("null");

NullComponent::NullComponent() = default;

std::string NullComponent::toString() {
    return "Null";
}

uint32_t NullComponent::generateId() {
    return 0;
}

std::vector<unsigned char> *NullComponent::serialise() {
    return new std::vector<unsigned char>();
}

Component *NullComponent::deserealise(std::vector<unsigned char> *bytes) {
    return this;
}