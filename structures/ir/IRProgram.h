#ifndef TKOM_INTERPRETER_IRPROGRAM_H
#define TKOM_INTERPRETER_IRPROGRAM_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "IRFunction.h"

class IRProgram {
public:
    typedef std::shared_ptr<IRProgram> ptr;

    void run();

    IRFunction::map definedFunctions;
};


#endif //TKOM_INTERPRETER_IRPROGRAM_H
