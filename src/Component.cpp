#include "Component.h"

using namespace CustomClasses;

void Component::addChild(CustomClasses::Component* component){
    component->parent = this;
    children[std::to_string(nextChildArrayIndex)] = component;
    nextChildArrayIndex++;
}

void Component::setChild(const std::string& key, CustomClasses::Component* component){
    component->parent = this;
    children[key] = component;
    nextChildArrayIndex++;
}

Component* Component::call(ArrayComponent* args){
    throw std::runtime_error("This object can not be called, object: '" + toString() + "'");
}

Component* Component::operator+(const Component& other){
    throw std::runtime_error("This operation is not supported");
}
Component* Component::operator-(const Component& other){
    throw std::runtime_error("This operation is not supported");
}
Component* Component::operator*(const Component& other){
    throw std::runtime_error("This operation is not supported");
}
Component* Component::operator/(const Component& other){
    throw std::runtime_error("This operation is not supported");
}

Component::~Component(){
    for(const auto& n : children) delete n.second;
}

uint32_t Component::getId(){
    if(hasIdExpired) id = generateId();
    hasIdExpired = false;
    return id;
}

std::vector<unsigned char>* Component::serialise() {
    throw std::runtime_error("A value of this type can not be serialised");
}

Component *Component::deserealise(std::vector<unsigned char>*) {
    throw std::runtime_error("A value of this type can not be deserialised");
}
