#ifndef TKOM_INTERPRETER_IRFUNCTION_H
#define TKOM_INTERPRETER_IRFUNCTION_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include "ContextPrototype.h" // circular dependency
#include "IRObject.h"
#include "IRExecutable.h"
#include "IRStatement.h"
#include "IRAssignable.h"
#include "IRReturnStatement.h"

class IRFunction{
public:
    typedef std::shared_ptr<IRFunction> ptr;
    typedef std::unordered_map<std::string, IRFunction::ptr> map;
    typedef IRStatement::StatementsList StatementsList;

    std::string returnTypeName;
    std::string functionName;

    ContextPrototype contextProto;
    StatementsList statements;

    IRObject::ptr execute(IRContext* upperContext, std::vector<IRObject::ptr> args){
        auto context = contextProto.createInstance(args);
        context->upperContext = upperContext;

        for(auto& s: statements){
            s->execute(context);
        }

        return nullptr;
    }
};

#endif //TKOM_INTERPRETER_IRFUNCTION_H
