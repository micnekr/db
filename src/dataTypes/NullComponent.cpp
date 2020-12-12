#include "NullComponent.h"

using namespace CustomClasses;

NullComponent::NullComponent() = default;

std::string NullComponent::toString() {
    return "null";
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

std::string NullComponent::toString(bool toJson) {
    return toString();
}
