#ifndef TKOM_INTERPRETER_IRRETURNSTATEMENT_H
#define TKOM_INTERPRETER_IRRETURNSTATEMENT_H

#include <string>
#include "IRObject.h"
#include "IRStatement.h"
#include "IRAssignable.h"

class IRReturnStatement : public IRStatement{
    IRAssignable::ptr value;
public:
    class ReturnException {
    public:
        IRObject::ptr value;
    };

    IRReturnStatement(IRAssignable::ptr val){
        value = val;
    }

    IRObject::ptr execute(IRContext* context) override {
        debug("Executing return statement");
        auto object = value->execute(context);
        throw ReturnException{object};
    }
};

#endif //TKOM_INTERPRETER_IRRETURNSTATEMENT_H
