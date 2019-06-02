#ifndef TKOM_INTERPRETER_IRWHILESTATEMENT_H
#define TKOM_INTERPRETER_IRWHILESTATEMENT_H

#include "IRStatement.h"
#include "IRAssignable.h"

class IRWhileStatement : public IRStatement {
    IRAssignable::ptr condition;
    IRStatement::StatementsList body;
public:
    IRWhileStatement(IRAssignable::ptr cond, IRStatement::StatementsList body){
        condition = cond;
        body = body;
    }

    // todo: execute()
};


#endif //TKOM_INTERPRETER_IRWHILESTATEMENT_H
