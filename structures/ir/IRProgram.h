#ifndef TKOM_INTERPRETER_IRPROGRAM_H
#define TKOM_INTERPRETER_IRPROGRAM_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "IRFunction.h"
#include "IRContext.h"

class IRProgram {
public:
    typedef std::shared_ptr<IRProgram> ptr;
    void run();

    std::unordered_map<std::string, IRFunction::ptr> definedFunctions;
    IRContext context;
};


#endif //TKOM_INTERPRETER_IRPROGRAM_H
