#ifndef TABLE_H // include guard
#define TABLE_H

#include "dataTypes/IdComponent.h"
#include "DataBase.h"
#include "dataTypes/functions/tableFunctions/SelectFunctionComponent.h"
#include <string>

namespace CustomClasses{
    class DataBase;

    class Table : public IdComponent{
        public:
            CustomClasses::DataBase* parentDatabase;
            Table(std::string, CustomClasses::DataBase*);
            std::string name;
    };
}

#endif