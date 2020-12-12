#ifndef NUMBER_COMPONENT_H // include guard
#define NUMBER_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>

namespace CustomClasses{

    class NumberComponent: public Component{
        public:
        double value;

        explicit NumberComponent(double);

        NumberComponent* setValue(double);

        Component* operator+(const Component&) override;
        Component* operator-(const Component&) override;
        Component* operator*(const Component&) override;
        Component* operator/(const Component&) override;

        std::string toString() override;
        std::string toString(bool toJson) override;
        uint32_t generateId() override;

        std::vector<unsigned char>* serialise() override;
        Component* deserealise(std::vector<unsigned char>*) override;
    };
}

#endif