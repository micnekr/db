//
// Created by misha on 12/12/2020.
//

#ifndef DB_INSERTFUNCTIONCOMPONENT_H
#define DB_INSERTFUNCTIONCOMPONENT_H

#include "../../FunctionComponent.h"

namespace CustomClasses{

    class InsertFunctionComponent: public FunctionComponent {
    public:
        InsertFunctionComponent() = default;

        std::string toString() override;

        Component* call(ArrayComponent* args) override;
    };
}


#endif //DB_INSERTFUNCTIONCOMPONENT_H
