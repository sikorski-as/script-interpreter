#ifndef TKOM_INTERPRETER_IRASSIGNABLE_H
#define TKOM_INTERPRETER_IRASSIGNABLE_H

#include <memory>
#include <string>

class IRAssignable {
public:
    typedef std::shared_ptr<IRAssignable> ptr;

    // todo: execute() implementation + inheritance

    std::string getType(){
        return "none"; // todo
    }
};


#endif //TKOM_INTERPRETER_IRASSIGNABLE_H
