#ifndef COMPONENT_H // include guard
#define COMPONENT_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdint.h>

namespace CustomClasses{
    enum ComponentTypes{
        ctFunction,
        ctArray,
        ctId,
        ctNull,
        ctNumber,
        ctString
    };

    class ArrayComponent;

    class Component{
        public:
        std::unordered_map<std::string, CustomClasses::Component*> children;
        int nextChildArrayIndex = 0;

        void addChild(CustomClasses::Component*);
        void setChild(std::string, CustomClasses::Component*);

        std::string virtual toString() = 0;

        virtual Component* call(ArrayComponent* args);

        virtual Component* operator+(const Component&);
        virtual Component* operator-(const Component&);
        virtual Component* operator*(const Component&);
        virtual Component* operator/(const Component&);

        uint32_t id = 0;

        virtual uint32_t getId() = 0;

        ~Component();
    };
}

#endif