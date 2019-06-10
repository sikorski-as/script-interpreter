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

    IRObject::ptr execute(IRContext* context) override {
        debug("Executing definiton of variable " + name);

        auto object = std::make_shared<IRObject>(*value->execute(context)); // copy assignment
        object->type = typeName;
        context->addSymbol(name, object);

        return nullptr;
    }
};

#endif //TKOM_INTERPRETER_IRVARDEFINITION_H
