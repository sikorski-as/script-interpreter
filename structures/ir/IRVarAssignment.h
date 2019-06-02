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

    // todo: execute()
};

#endif //TKOM_INTERPRETER_IRVARASSIGNMENT_H
