#ifndef STRING_COMPONENT_H // include guard
#define STRING_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

namespace CustomClasses{

    class StringComponent: public Component{
        public:
        std::string value;

        explicit StringComponent(std::string);
        explicit StringComponent(Component*);

        StringComponent* setValue(std::string);

        Component* operator+(const Component&) override;

        std::string toString() override;
        std::string toString(bool toJson) override;

        uint32_t generateId() override;

        std::vector<unsigned char>* serialise() override;
        Component* deserealise(std::vector<unsigned char>*) override;
    };
}

#endif