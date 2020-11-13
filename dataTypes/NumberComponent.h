#ifndef NUMBER_COMPONENT_H // include guard
#define NUMBER_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>
#include <cstring>

namespace CustomClasses{

    class NumberComponent: public Component{
        public:
        double value;

        NumberComponent(double);

        NumberComponent* setValue(double);

        Component* operator+(const Component&);
        Component* operator-(const Component&);
        Component* operator*(const Component&);
        Component* operator/(const Component&);

        std::string toString();
        uint32_t generateId();
    };
}

#endif