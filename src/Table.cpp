#include "Table.h"

using namespace CustomClasses;

Table::Table(std::string _name, CustomClasses::DataBase* _parentDatabase){
    name = _name;
    parentDatabase = _parentDatabase;
    className = "Table";

    //add the table functions
    setChild("select", new SelectFunctionComponent());
}
