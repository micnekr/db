#include "ArrayComponent.h"

using namespace CustomClasses;

std::string ArrayComponent::toString(){
    return toString(false);
}

std::string ArrayComponent::toString(bool toJson) {
    return IdComponent::toString(toJson);

    // //check if it is an object with keys as ints
    // bool allPositiveInts = true;
    // for(auto &iterator : children){
    //     //if not a positive integer, break
    //     if(iterator.first.find_first_not_of( "0123456789" ) != std::string::npos){
    //         allPositiveInts = false;
    //         break;
    //     }
    // }

    // //if not all are ints, return as an object
    // if(!allPositiveInts) return IdComponent::toString();

    // std::string out = "[";

    // int lastInt = -1;
    // for(auto &iterator : children) {
    //     int key;
    //     try{
    //         key = std::stoi(iterator.first);
    //         lastInt++;
    //     }catch(const std::exception& ex) {
    //         return IdComponent::toString();
    //     }
    //     out += iterator.second->toString();
    // }
    // return out + "]";
}
