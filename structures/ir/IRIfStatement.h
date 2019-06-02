#ifndef TKOM_INTERPRETER_IRIFSTATEMENT_H
#define TKOM_INTERPRETER_IRIFSTATEMENT_H

#include "IRStatement.h"
#include "IRAssignable.h"

class IRIfStatement : public IRStatement {
    IRAssignable::ptr condition;
    IRStatement::StatementsList trueBlock, falseBlock;
public:
    IRIfStatement(IRAssignable::ptr cond, IRStatement::StatementsList tblock, IRStatement::StatementsList fblock){
        condition = cond;
        trueBlock = tblock;
        falseBlock = fblock;
    }

    // todo: execute()

};


#endif //TKOM_INTERPRETER_IRIFSTATEMENT_H
