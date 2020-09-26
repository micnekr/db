#include "Table.h"

using namespace CustomClasses;

Table::Table(std::string _name, CustomClasses::DataBase* _parentDatabase){
    name = _name;
    parentDatabase = _parentDatabase;

    //add the table functions
    addChild(new SelectFunctionComponent());
}

std::string Table::toString(){
    return name;
}