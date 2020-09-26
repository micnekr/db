#ifndef TABLE_H // include guard
#define TABLE_H

#include "Component.h"
#include "DataBase.h"
#include "dataTypes/functions/tableFunctions/SelectFunctionComponent.h"
#include <string>

namespace CustomClasses{
    class DataBase;

    class Table : public Component{
        public:
            std::string name;
            CustomClasses::DataBase* parentDatabase;
            Table(std::string, CustomClasses::DataBase*);
            std::string toString();
    };
}

#endif