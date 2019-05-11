#ifndef TKOM_INTERPRETER_IFSTATEMENT_H
#define TKOM_INTERPRETER_IFSTATEMENT_H

#include "Statement.h"
#include "Assignable.h"
#include "BlockStatement.h"

class IfStatement : public Statement{
public:
    IfStatement(Assignable::ptr condition, BlockStatement::ptr trueBlock, BlockStatement::ptr falseBlock)
    : condition(condition), trueBlock(trueBlock), falseBlock(falseBlock)
    {

    }

    ASTNode::Type getType() const override {
        return Type::if_statement;
    }

    Assignable::ptr condition;
    BlockStatement::ptr trueBlock;
    BlockStatement::ptr falseBlock;

};


#endif //TKOM_INTERPRETER_IFSTATEMENT_H
