#ifndef DATABASE_H // include guard
#define DATABASE_H

#include "dataTypes/IdComponent.h"
#include "Table.h"
#include "Token.h"
#include "MapFile.h"
#include <iostream>
#include <string>
#include <vector>
#include <system_error>
#include <stdint.h>

namespace CustomClasses{
    class Table;

    class DataBase : public IdComponent{
        public:
        DataBase(std::string, MapFile*, MapFile*);
        DataBase(std::string, std::string, std::string, int, int);
        DataBase() = delete;
        std::string name;
        MapFile* primaryMap;
        MapFile* secondaryMap;

        void createTable(std::string);

        void store(uint32_t, Component*);
    };
}

#endif