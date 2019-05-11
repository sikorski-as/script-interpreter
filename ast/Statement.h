#ifndef TKOM_INTERPRETER_STATEMENT_H
#define TKOM_INTERPRETER_STATEMENT_H

#include "ASTNode.h"

class Statement : public ASTNode{
public:
    typedef std::shared_ptr<Statement> ptr;

    virtual ~Statement() = default;
};


#endif //TKOM_INTERPRETER_STATEMENT_H
