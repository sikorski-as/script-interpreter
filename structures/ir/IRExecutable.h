#ifndef TKOM_INTERPRETER_IREXECUTABLE_H
#define TKOM_INTERPRETER_IREXECUTABLE_H

#include <memory>
#include <vector>
#include <unordered_map>
#include "IRContext.h"

class IRContext;
class IRExecutable {
public:
    typedef std::shared_ptr<IRExecutable> ptr;
    typedef std::vector<std::shared_ptr<IRExecutable>> ExecutableList;

    virtual IRObject::ptr execute(IRContext* context) = 0;

    virtual void debug(std::string s){
        std::cout << s << std::endl;
    }
};


#endif //TKOM_INTERPRETER_IREXECUTABLE_H
