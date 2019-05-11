#ifndef TKOM_INTERPRETER_FUNCTIONCALL_H
#define TKOM_INTERPRETER_FUNCTIONCALL_H

#include <string>
#include <initializer_list>
#include <vector>
#include "Assignable.h"
#include "Statement.h"

class FunctionCall : public Assignable, public Statement{
public:
    explicit FunctionCall() = default;

    FunctionCall(std::string functionName, std::initializer_list<Assignable::ptr> arguments = {})
    : functionName(functionName), arguments(arguments)
    {

    }

    virtual ~FunctionCall() = default;

    Type getType() const override {
        return Type::function_call;
    }

    std::string functionName;
    std::vector<Assignable::ptr> arguments;
};


#endif //TKOM_INTERPRETER_FUNCTIONCALL_H
