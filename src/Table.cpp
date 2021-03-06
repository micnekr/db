#include "Table.h"
#include "dataTypes/functions/tableFunctions/InsertFunctionComponent.h"

#include <utility>

using namespace CustomClasses;

Table::Table(std::string _name, CustomClasses::DataBase* _parentDatabase){
    name = std::move(_name);
    parentDatabase = _parentDatabase;
    className = "Table";

    //add the table functions
    setChild("select", new SelectFunctionComponent());
    setChild("insert", new InsertFunctionComponent());
}
