#ifndef TKOM_INTERPRETER_IRVARDEFINITION_H
#define TKOM_INTERPRETER_IRVARDEFINITION_H

#include <string>
#include "IRStatement.h"
#include "IRAssignable.h"

class IRVarDefinition : public IRStatement{
    std::string typeName, name;
    IRAssignable::ptr value;
public:
    IRVarDefinition(std::string& type_name, std::string& variable_name, IRAssignable::ptr val){
        typeName = type_name;
        name = variable_name;
        value = val;
    }

    // todo: execute()
};

#endif //TKOM_INTERPRETER_IRVARDEFINITION_H
