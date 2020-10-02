#ifndef TABLE_H // include guard
#define TABLE_H

#include "Component.h"
#include "DataBase.h"
#include "dataTypes/functions/tableFunctions/SelectFunctionComponent.h"
#include "dataTypes/IdComponent.h"
#include <string>

namespace CustomClasses{
    class DataBase;

    class Table : public IdComponent{
        public:
            CustomClasses::DataBase* parentDatabase;
            Table(std::string, CustomClasses::DataBase*);
    };
}

#endif