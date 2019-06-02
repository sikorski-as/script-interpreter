#ifndef TKOM_INTERPRETER_IRRETURNSTATEMENT_H
#define TKOM_INTERPRETER_IRRETURNSTATEMENT_H

#include <string>
#include "IRStatement.h"
#include "IRAssignable.h"

class IRReturnStatement : public IRStatement{
    IRAssignable::ptr value;
public:
    IRReturnStatement(IRAssignable::ptr val){
        value = val;
    }

    // todo: execute()

    class ReturnException {
        IRAssignable::ptr value;
    };
};

#endif //TKOM_INTERPRETER_IRRETURNSTATEMENT_H
