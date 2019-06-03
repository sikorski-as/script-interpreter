#ifndef TKOM_INTERPRETER_IRIFSTATEMENT_H
#define TKOM_INTERPRETER_IRIFSTATEMENT_H

#include <variant>
#include <memory>
#include "IRStatement.h"
#include "IRAssignable.h"
#include "IRObject.h"

class IRIfStatement : public IRStatement {
    IRAssignable::ptr condition;
    IRStatement::StatementsList trueBlock, falseBlock;
public:
    IRIfStatement(IRAssignable::ptr cond, IRStatement::StatementsList tblock, IRStatement::StatementsList fblock){
        condition = cond;
        trueBlock = tblock;
        falseBlock = fblock;
    }

    IRObject::ptr execute(IRContext* context) override {
        auto thisContext = new IRContext(context);
        debug("Execution of if statement");

        auto object = condition->execute(context);
        auto boolean = std::get<bool>(object->value);
        if(boolean){
            debug("Executing true block");
            for(auto& s: trueBlock){
                s->execute(thisContext);
            }
        }
        else{
            debug("Executing else block");
            for(auto& s: falseBlock){
                s->execute(thisContext);
            }
        }
        debug("Execution of if statement ended");

        delete thisContext;
        return nullptr;
    }

};


#endif //TKOM_INTERPRETER_IRIFSTATEMENT_H
