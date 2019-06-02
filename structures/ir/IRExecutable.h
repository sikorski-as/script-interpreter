#ifndef TKOM_INTERPRETER_IREXECUTABLE_H
#define TKOM_INTERPRETER_IREXECUTABLE_H

#include <memory>
#include <unordered_map>
#include "IRContext.h"

class IRExecutable {
public:
    typedef std::shared_ptr<IRExecutable> ptr;

    virtual IRObject::ptr execute(IRContext* context) = 0;
};


#endif //TKOM_INTERPRETER_IREXECUTABLE_H
