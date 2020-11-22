#ifndef ID_COMPONENT_H // include guard
#define ID_COMPONENT_H

#include "../Config.h"

#include "../Component.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <random>
#include <ctime>

namespace CustomClasses{

    class IdComponent: public Component{
        public:
        static std::mt19937 mt_rand;
        static uint32_t componentCounter;

        std::string className = "";

        std::string toString() override;
        uint32_t generateId() override;
    };
}

#endif