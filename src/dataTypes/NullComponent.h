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

        std::string toString() override;
        uint32_t generateId() override;

        const static std::size_t hashValue;

        std::vector<unsigned char>* serialise() override;
        Component* deserealise(std::vector<unsigned char>*) override;
    };
}

#endif