#include "DataBase.h"
#include "Component.h"

using namespace CustomClasses;

DataBase::DataBase(std::string _name, MapFile* _primaryMap, MapFile* _secondaryMap){
    if(_primaryMap == nullptr || _secondaryMap == nullptr) throw "Null map files in database constructor";

    primaryMap = _primaryMap;
    secondaryMap = _secondaryMap;

    className = "Database";
    name = _name;

    
}

DataBase::DataBase(std::string _name, std::string primaryMapPath, std::string secondaryMapPath, int primaryAllocatedSpace, int secondaryAllocatedSpace){
    try{
        primaryMap = new MapFile(primaryMapPath, primaryAllocatedSpace);
        secondaryMap = new MapFile(secondaryMapPath, secondaryAllocatedSpace);
    }catch (const std::system_error& e){
        throw "Files could not be opened or created";
    }
}

void DataBase::createTable(std::string name){
    Table* newTablePtr = new Table(name, this);
    setChild(name, newTablePtr);
}

void DataBase::store(uint32_t index, Component* value){
    primaryMap->set(index, 65 * 256 + 66);
}