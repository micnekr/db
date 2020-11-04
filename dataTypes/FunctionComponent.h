#ifndef FUNCTION_COMPONENT_H // include guard
#define FUNCTION_COMPONENT_H

#include "../Component.h"
#include "IdComponent.h"
#include "ArrayComponent.h"
#include <iostream>
#include <string>

namespace CustomClasses{

    class FunctionComponent: public IdComponent{
        public:
        FunctionComponent* setValue();

        void operator+(const FunctionComponent&);
        void operator-(const FunctionComponent&);
        void operator*(const FunctionComponent&);
        void operator/(const FunctionComponent&);

        virtual std::string toString() = 0;

        virtual Component* call(ArrayComponent* args) = 0;
    };
}

#endif