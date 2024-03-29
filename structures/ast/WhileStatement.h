#ifndef TKOM_INTERPRETER_WHILESTATEMENT_H
#define TKOM_INTERPRETER_WHILESTATEMENT_H

#include "Statement.h"
#include "Assignable.h"
#include "BlockStatement.h"

class WhileStatement : public Statement{
public:
    WhileStatement(Assignable::ptr condition, BlockStatement::ptr body)
    : condition(condition), body(body)
    {

    }

    Type getType() const override {
        return Type::while_statement;
    }

    Assignable::ptr condition;
    BlockStatement::ptr body;


    std::string representation() const override {
        return "While statement";
    };

    ChildrenList getChildren() override {
        return ChildrenList({condition, body});
    }
};


#endif //TKOM_INTERPRETER_WHILESTATEMENT_H
