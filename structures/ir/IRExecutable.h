#ifndef TKOM_INTERPRETER_IREXECUTABLE_H
#define TKOM_INTERPRETER_IREXECUTABLE_H

#include "../../settings.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "IRContext.h"

class IRContext;
class IRExecutable {
public:
    typedef std::shared_ptr<IRExecutable> ptr;
    typedef std::vector<std::shared_ptr<IRExecutable>> ExecutableList;
    class RuntimeError{
    public:
        std::string reason;
    };

    virtual IRObject::ptr execute(IRContext* context) = 0;

    virtual void debug(std::string s){
#ifdef TKOM_DEBUG
        std::cout << s << std::endl;
#endif
    }
};


#endif //TKOM_INTERPRETER_IREXECUTABLE_H
