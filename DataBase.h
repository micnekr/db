#ifndef DATABASE_H // include guard
#define DATABASE_H

#include "dataTypes/IdComponent.h"
#include "Table.h"
#include "Token.h"
#include <iostream>
#include <string>
#include <vector>

namespace CustomClasses{
    class Table;

    class DataBase : public IdComponent{
        public:
        DataBase(std::string);
        DataBase() = delete;
        std::string name;

        void createTable(std::string);
    };
}

#endif