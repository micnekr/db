#ifndef ID_COMPONENT_H // include guard
#define ID_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>

namespace CustomClasses{

    class IdComponent: public Component{
        public:
        std::string name;

        IdComponent(std::string);
        IdComponent();

        IdComponent* setValue(std::string);

        std::string toString();
    };
}

#endif