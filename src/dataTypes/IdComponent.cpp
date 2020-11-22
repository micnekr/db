#include "IdComponent.h"

using namespace CustomClasses;

uint32_t IdComponent::componentCounter = 0;
std::mt19937 IdComponent::mt_rand = std::mt19937(std::time(0));

std::string IdComponent::toString(){
    // if it is an object
    if(children.find("__value") == children.end()){
        std::string out = "";
        if(className != "") out += "<" + className + "> ";
        out += "{\n";
        for(auto& iterator: children){
            std::string key = iterator.first;
            std::string value = iterator.second->toString();

            //indent
            std::string formatedValue = "";
            for(int i = 0; i < value.size(); i++){
                char currentChar = value[i];
                formatedValue += currentChar;

                if(currentChar == '\n') formatedValue += "\t";
            }

            out += "\t" + key + ":" + formatedValue + "\n";
        }
        return out += "}";
    }else return children["__value"]->toString();
}

uint32_t IdComponent::generateId(){
    //random int based approach

    int randomBytesInObjectId = Config::getInstance().randomBytesInObjectId;
    int timeBytesInObjectId = Config::getInstance().timeBytesInObjectId;
    int counterBytesInObjectId = Config::getInstance().counterBytesInObjectId;

    uint32_t value;

    uint32_t mask;
    if(randomBytesInObjectId > 0) mask = (uint32_t(1) << randomBytesInObjectId * 8) - 1;
    else mask = 0;

    value = mask & IdComponent::mt_rand();

    if(timeBytesInObjectId > 0) mask = (uint32_t(1) << timeBytesInObjectId * 8) - 1;
    else mask = 0;

    //shift the value
    value <<= timeBytesInObjectId * 8;
    value += uint32_t(std::time(0)) & mask;

    if(counterBytesInObjectId > 0) mask = (uint32_t(1) << counterBytesInObjectId * 8) - 1;
    else mask = 0;

    //shift the value
    value <<= timeBytesInObjectId * 8;
    value += IdComponent::componentCounter & mask;

    //increment the counter
    IdComponent::componentCounter = (IdComponent::componentCounter + 1) & mask;

    return value;
}
