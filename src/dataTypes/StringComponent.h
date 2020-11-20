#ifndef STRING_COMPONENT_H // include guard
#define STRING_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>

namespace CustomClasses{

    class StringComponent: public Component{
        public:
        std::string value;

        StringComponent(std::string);

        StringComponent* setValue(std::string);

        Component* operator+(const Component&);

        std::string toString();

        uint32_t generateId();
    };
}

#endif