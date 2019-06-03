#ifndef TKOM_INTERPRETER_IRVARASSIGNMENT_H
#define TKOM_INTERPRETER_IRVARASSIGNMENT_H

#include <string>
#include "IRStatement.h"
#include "IRAssignable.h"

class IRVarAssignment : public IRStatement{
    std::string name;
    IRAssignable::ptr value;
public:
    IRVarAssignment(std::string& variable_name, IRAssignable::ptr val){
        name = variable_name;
        value = val;
    }

    IRObject::ptr execute(IRContext* context) override {
        debug("Executing assignment to variable " + name);

        auto o = value->execute(context);
        auto object = *(o);

        context->setSymbol(name, std::make_shared<IRObject>(object)); // copy assignment

        return nullptr;
    }
};

#endif //TKOM_INTERPRETER_IRVARASSIGNMENT_H
