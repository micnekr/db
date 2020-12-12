#ifndef CONNECTION_H // include guard
#define CONNECTION_H

#include "Component.h"
#include "Token.h"
#include "DataBase.h"
#include "Table.h"
#include "dataTypes/NumberComponent.h"
#include "dataTypes/StringComponent.h"
#include "dataTypes/IdComponent.h"
#include "dataTypes/NullComponent.h"
#include "dataTypes/ArrayComponent.h"

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

namespace CustomClasses{

    class Connection{
        public:
            CustomClasses::IdComponent* globalIdComponent;
            Connection(std::vector<CustomClasses::DataBase*>*, CustomClasses::DataBase*, CustomClasses::IdComponent*);

            CustomClasses::DataBase* selectedDataBase;
            std::vector<CustomClasses::DataBase*>* dataBases;
            Component * execute(Token*);
        private:
            Component* computeQuery(Token*, Component*);
    };
}

#endif