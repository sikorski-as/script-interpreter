#ifndef TKOM_INTERPRETER_ASSIGNABLE_H
#define TKOM_INTERPRETER_ASSIGNABLE_H

#include "ASTNode.h"

class Assignable : public ASTNode{
public:
    typedef std::shared_ptr<Assignable> ptr;

    virtual ~Assignable() = default;
};


#endif //TKOM_INTERPRETER_ASSIGNABLE_H
