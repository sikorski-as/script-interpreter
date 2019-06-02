#ifndef TKOM_INTERPRETER_IRFUNCTION_H
#define TKOM_INTERPRETER_IRFUNCTION_H

#include <memory>
#include <unordered_map>
#include <string>
#include "IRObject.h"
#include "IRFunction.h"
#include "ContextPrototype.h"
#include "IRExecutable.h"
#include "IRStatement.h"

class IRFunction : public IRExecutable{
public:
    typedef std::shared_ptr<IRFunction> ptr;
    typedef std::unordered_map<std::string, IRFunction::ptr> map;
    typedef IRStatement::StatementsList StatementsList;

    std::string returnTypeName;
    std::string functionName;

    ContextPrototype contextProto;
    StatementsList statements;

    IRObject::ptr execute(IRContext*) override{
        // todo
        return nullptr;
    };
};

#endif //TKOM_INTERPRETER_IRFUNCTION_H
