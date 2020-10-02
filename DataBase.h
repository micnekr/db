#ifndef DATABASE_H // include guard
#define DATABASE_H

#include "Component.h"

#include "Table.h"
#include "Token.h"
#include "dataTypes/IdComponent.h"
#include <iostream>
#include <string>
#include <vector>

namespace CustomClasses{
    class Table;

    class DataBase : public IdComponent{
        public:
        DataBase(std::string);

        void createTable(std::string);
        std::string print();
    };
}

#endif