#ifndef TKOM_INTERPRETER_VARIABLEASSIGNMENT_H
#define TKOM_INTERPRETER_VARIABLEASSIGNMENT_H


#include <string>
#include "Statement.h"
#include "Assignable.h"

class VariableAssignment : public Statement{
public:
    VariableAssignment(std::string name, Assignable::ptr value)
            : name(name), value(value)
    {

    }

    Type getType() const override {
        return Type::var_assignment;
    }

    std::string name;
    Assignable::ptr value;
};


#endif //TKOM_INTERPRETER_VARIABLEASSIGNMENT_H
