#ifndef NULL_COMPONENT_H // include guard
#define NULL_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>

namespace CustomClasses{

    class NullComponent: public Component{
        public:

        NullComponent();

        std::string toString();
        uint32_t generateId();

        const static std::size_t hashValue;
    };
}

#endif