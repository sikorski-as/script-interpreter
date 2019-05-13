#ifndef TKOM_INTERPRETER_METHODCALL_H
#define TKOM_INTERPRETER_METHODCALL_H

#include "FunctionCall.h"

class MethodCall : public FunctionCall{
public:
    explicit MethodCall() = default;

    MethodCall(std::string objectName, std::string functionName, std::initializer_list<Assignable::ptr> arguments = {})
    : FunctionCall(functionName, arguments), objectName(objectName)
    {

    }

    Type getType() const override
    {
        return Type::method_call;
    }

    std::string representation() const override {
        return "Method call of " + objectName + "." + functionName;
    };

    std::string objectName;
};


#endif //TKOM_INTERPRETER_METHODCALL_H
