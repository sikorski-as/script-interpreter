#ifndef TKOM_INTERPRETER_IRVARIABLE_H
#define TKOM_INTERPRETER_IRVARIABLE_H

#include <memory>
#include "IRAssignable.h"

class IRVariable : public IRAssignable{
public:
    typedef std::shared_ptr<IRVariable> ptr;

    std::string variableName;

    IRVariable(std::string& vartype, std::string& varname){
        assignableType = vartype;
        variableName = varname;
    }

    IRObject::ptr execute(IRContext* context) override{
        return std::make_shared<IRObject>(*context->getSymbol(variableName));
    }
};


#endif //TKOM_INTERPRETER_IRVARIABLE_H
