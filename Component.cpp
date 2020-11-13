#include "Component.h"

using namespace CustomClasses;

void Component::addChild(CustomClasses::Component* component){
    children[std::to_string(nextChildArrayIndex)] = component;
    nextChildArrayIndex++;
}

void Component::setChild(std::string key, CustomClasses::Component* component){
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
    std::cout << "destroyed a component\n";
}

uint32_t Component::getId(){
    if(hasIdExpired) id = generateId();
    hasIdExpired = false;
    return id;
}