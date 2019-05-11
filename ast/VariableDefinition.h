#ifndef TKOM_INTERPRETER_VARIABLEDEFINITION_H
#define TKOM_INTERPRETER_VARIABLEDEFINITION_H

#include <string>
#include "Statement.h"
#include "Assignable.h"

class VariableDefinition : public Statement{
public:
    VariableDefinition(std::string name, std::string typeName, Assignable::ptr value)
            : name(name), typeName(typeName), value(value)
    {

    }

    Type getType() const override {
        return Type::var_definition;
    }

    std::string name;
    std::string typeName;
    Assignable::ptr value;
};

#endif //TKOM_INTERPRETER_VARIABLEDEFINITION_H
