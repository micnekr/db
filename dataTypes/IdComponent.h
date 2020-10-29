#ifndef ID_COMPONENT_H // include guard
#define ID_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace CustomClasses{

    class IdComponent: public Component{
        public:
        std::string className = "";

        std::string toString();
    };
}

#endif