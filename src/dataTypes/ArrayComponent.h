#ifndef ARRAY_COMPONENT_H // include guard
#define ARRAY_COMPONENT_H

#include "../Component.h"
#include "IdComponent.h"
#include <iostream>
#include <vector>
#include <string>

namespace CustomClasses{
    class ArrayComponent: public IdComponent{
        public:
        std::string toString();
    };
}

#endif