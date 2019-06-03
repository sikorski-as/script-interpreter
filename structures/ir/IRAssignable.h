#ifndef TKOM_INTERPRETER_IRASSIGNABLE_H
#define TKOM_INTERPRETER_IRASSIGNABLE_H

#include <memory>
#include <string>
#include "IRExecutable.h"

class IRAssignable : public IRExecutable{
public:
    typedef std::shared_ptr<IRAssignable> ptr;
    std::string assignableType;

    virtual std::string getType(){
        return assignableType;
    }
};


#endif //TKOM_INTERPRETER_IRASSIGNABLE_H
