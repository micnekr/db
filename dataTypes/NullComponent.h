#ifndef NULL_COMPONENT_H // include guard
#define NULL_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>

namespace CustomClasses{

    class NullComponent: public Component{
        public:

        NullComponent();

        std::string toString();
    };
}

#endif