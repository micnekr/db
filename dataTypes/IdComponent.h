#ifndef ID_COMPONENT_H // include guard
#define ID_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdint.h>

namespace CustomClasses{

    class IdComponent: public Component{
        public:
        std::string className = "";

        std::string toString();
        uint32_t getId();
    };
}

#endif