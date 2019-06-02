#ifndef TKOM_INTERPRETER_IRFUNCTIONCALL_H
#define TKOM_INTERPRETER_IRFUNCTIONCALL_H

#include <memory>
#include <string>
#include <vector>
#include "IRStatement.h"
#include "IRAssignable.h"

class IRFunctionCall : public IRStatement, public IRAssignable{
    std::vector<IRAssignable::ptr> arguments;
public:
    typedef std::shared_ptr<IRFunctionCall> ptr;

    IRFunctionCall(std::string fname){
        functionName = fname;
        returnType = "none";
    }

    void addArgument(IRAssignable::ptr arg){
        arguments.push_back(arg);
    }

    std::string functionName;
    std::string returnType;

    std::string getType() override {
        return returnType;
    }

    IRObject::ptr execute(IRContext*) override{
        return nullptr; // todo
    }
};


#endif //TKOM_INTERPRETER_IRFUNCTIONCALL_H
