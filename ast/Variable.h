#ifndef TKOM_INTERPRETER_VARIABLE_H
#define TKOM_INTERPRETER_VARIABLE_H

#include <string>
#include "Assignable.h"

class Variable : public Assignable{
public:
    explicit Variable() = default;

    explicit Variable(std::string name)
    : name(name)
    {

    }

    Type getType() const override {
        return Type::variable;
    }

    std::string name;
};


#endif //TKOM_INTERPRETER_VARIABLE_H
