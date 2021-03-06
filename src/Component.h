#ifndef COMPONENT_H // include guard
#define COMPONENT_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

namespace CustomClasses{

    class ArrayComponent;

    class Component{
        public:
        std::unordered_map<std::string, CustomClasses::Component*> children;
        int nextChildArrayIndex = 0;

        Component* parent;

        void addChild(CustomClasses::Component*);
        void setChild(const std::string&, CustomClasses::Component*);

        virtual std::string toString() = 0;
        virtual std::string toString(bool) = 0;

        virtual Component* call(ArrayComponent* args);

        virtual Component* operator+(const Component&);
        virtual Component* operator-(const Component&);
        virtual Component* operator*(const Component&);
        virtual Component* operator/(const Component&);

        uint32_t id = 0;
        bool hasIdExpired = true;

        virtual uint32_t generateId() = 0;
        uint32_t getId();

        virtual std::vector<unsigned char>* serialise();
        virtual Component* deserealise(std::vector<unsigned char>*);

        virtual ~Component();
    };
}

#endif