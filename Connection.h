#ifndef CONNECTION_H // include guard
#define CONNECTION_H

#include "Component.h"
#include "Token.h"
#include "DataBase.h"
#include "Table.h"
#include "dataTypes/NumberComponent.h"
#include "dataTypes/StringComponent.h"
#include <vector>
#include <string>
#include <iostream>

namespace CustomClasses{

    class Connection{
        public:
            Connection(std::vector<CustomClasses::DataBase*>*, int);
            int selectedDataBaseIndex;
            std::vector<CustomClasses::DataBase*>* dataBases;
            void execute(Token*);
        private:
            Component* computeQuery(Token*, Component*);
    };
}

#endif