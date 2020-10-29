#include "DataBase.h"
#include "Component.h"

using namespace CustomClasses;

DataBase::DataBase(std::string _name){
    className = "Database";
    name = _name;
}

void DataBase::createTable(std::string name){
    Table* newTablePtr = new Table(name, this);
    setChild(name, newTablePtr);
}