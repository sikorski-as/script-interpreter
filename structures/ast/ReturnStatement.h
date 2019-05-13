#ifndef TKOM_INTERPRETER_RETURNSTATEMENT_H
#define TKOM_INTERPRETER_RETURNSTATEMENT_H

#include "Statement.h"
#include "Assignable.h"

class ReturnStatement : public Statement {
public:
    ReturnStatement(Assignable::ptr value = nullptr)
    : returnedValue(value)
    {

    }

    Type getType() const override {
        return Type::return_statement;
    }

    Assignable::ptr returnedValue;

    std::string representation() const override {
        return "Return statement";
    };

    ChildrenList getChildren() override {
        return ChildrenList({returnedValue});
    }
};


#endif //TKOM_INTERPRETER_RETURNSTATEMENT_H
