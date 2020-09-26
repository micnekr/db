#ifndef DATABASE_H // include guard
#define DATABASE_H

#include "Component.h"

#include "Table.h"
#include "Token.h"
#include <iostream>
#include <string>
#include <vector>

namespace CustomClasses{
    class Table;

    class DataBase : public Component{
        public:
        std::string name;

        DataBase(std::string);

        void createTable(std::string);
        std::string toString();
    };
}

#endif