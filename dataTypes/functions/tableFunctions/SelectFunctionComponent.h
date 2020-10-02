#ifndef SELECT_FUNCTION_COMPONENT_H // include guard
#define SELECT_FUNCTION_COMPONENT_H

#include "../../FunctionComponent.h"
#include "../../StringComponent.h"
#include "../../ArrayComponent.h"
#include <iostream>
#include <string>

namespace CustomClasses{

    class SelectFunctionComponent: public FunctionComponent {
        public:
        SelectFunctionComponent();

        std::string toString();

        Component* call(ArrayComponent* args);
    };
}

#endif