#include "Component.h"

using namespace CustomClasses;

void Component::addChild(CustomClasses::Component* component){
    std::cout << "add inner\n";
    children.push_back(component);
}

Component* Component::call(Component* args[]){
    throw std::runtime_error("This object can not be called");
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