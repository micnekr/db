#include "DataBase.h"

using namespace CustomClasses;

DataBase::DataBase(std::string _name){
    name = _name;
}

void DataBase::createTable(std::string name){
    Table* newTablePtr = new Table(name, this);
    std::cout << "add\n";
    addChild(newTablePtr);
    std::cout << "add\n";
}

std::string DataBase::print(){
    std::string out = "";
    out += name + "\n\n";
    for(int i = 0; i < children.size(); i++){
        out += i + " |" + children.at(i)->toString() + "\n";
    }

    return out;
}

