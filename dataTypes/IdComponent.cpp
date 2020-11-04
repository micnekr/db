#include "IdComponent.h"

using namespace CustomClasses;

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

uint32_t IdComponent::getId(){
    IdComponent* ptr = this;
    uint32_t value = (uint32_t) ptr;
    std::cout << value << "\n";
    return value;
}