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

        const static std::size_t hashValue;
    };
}

//add the hash functions
namespace std{
    template<> struct hash<CustomClasses::NullComponent>{
        std::size_t operator()(CustomClasses::NullComponent const& nullComponent) const noexcept
        {
            return CustomClasses::NullComponent::hashValue;
        }
    };
}

#endif