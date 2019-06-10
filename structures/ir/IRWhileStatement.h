#ifndef TKOM_INTERPRETER_IRWHILESTATEMENT_H
#define TKOM_INTERPRETER_IRWHILESTATEMENT_H

#include <iostream>
#include "IRStatement.h"
#include "IRAssignable.h"

class IRWhileStatement : public IRStatement {
    IRAssignable::ptr condition;
    IRStatement::StatementsList body;
public:
    IRWhileStatement(IRAssignable::ptr cond, IRStatement::StatementsList body){
        condition = cond;
        this->body = body;
    }

    IRObject::ptr execute(IRContext* context) override {
        auto thisContext = new IRContext(context);

        debug("Execution while loop");
        while(std::get<bool>(condition->execute(thisContext)->value)){
            debug("Iteration of while loop starts");
            for(auto& s: body){
                s->execute(thisContext);
            }
        }
        debug("Execution of while loop ended");

        delete thisContext;
        return nullptr;
    }
};


#endif //TKOM_INTERPRETER_IRWHILESTATEMENT_H
