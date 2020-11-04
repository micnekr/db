#ifndef STRING_COMPONENT_H // include guard
#define STRING_COMPONENT_H

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>

namespace CustomClasses{

    class StringComponent: public Component{
        public:
        std::string value;

        StringComponent(std::string);

        StringComponent* setValue(std::string);

        Component* operator+(const Component&);

        std::string toString();

        uint32_t getId();
    };
}

//add the hash functions
namespace std{
    template<> struct hash<CustomClasses::StringComponent>{
        std::size_t operator()(CustomClasses::StringComponent const& stringComponent) const noexcept
        {
            std::size_t hash = std::hash<std::string>{}(stringComponent.value);
            return hash; // or use boost::hash_combine
        }
    };
}

#endif