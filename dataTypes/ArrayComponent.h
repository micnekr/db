#ifndef ARRAY_COMPONENT_H // include guard
#define ARRAY_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>

namespace CustomClasses{
    class ArrayComponent: public Component{
        public:
        std::vector<Component*> value;

        ArrayComponent* addValue(Component*);

        std::string toString();
    };
}

#endif