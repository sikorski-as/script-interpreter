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

    IRObject::ptr execute(IRContext* context) override{
        IRStatement::debug("Executing function " + functionName);

        std::vector<IRObject::ptr> args;
        for(auto& arg: arguments){
            args.push_back(arg->execute(context));
        }

        if(StdLib::hasFunction(functionName)){
            return StdLib::libraryFunctionCall(functionName, args);
        }
        else{
            auto function = context->getFunction(functionName);
            //auto new_context = function->contextProto.createInstance(args);
            //new_context->upperContext = context;

            try{
                function->execute(context, args);
            }
            catch(IRReturnStatement::ReturnException e){
                //delete new_context;
                return e.value;
            }
        }
        IRStatement::debug("Execution of function " + functionName + " ended");

        return nullptr;
    }
};


#endif //TKOM_INTERPRETER_IRFUNCTIONCALL_H
