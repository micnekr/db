#ifndef COMPONENT_H // include guard
#define COMPONENT_H

#include <iostream>
#include <string>
#include <vector>

namespace CustomClasses{
    class ArrayComponent;

    class Component{
        public:
        std::vector<CustomClasses::Component*> children;

        void addChild(CustomClasses::Component*);

        std::string virtual toString() = 0;

        virtual Component* call(ArrayComponent* args);

        virtual Component* operator+(const Component&);
        virtual Component* operator-(const Component&);
        virtual Component* operator*(const Component&);
        virtual Component* operator/(const Component&);
    };
}

#endif