#ifndef TKOM_INTERPRETER_LITERAL_H
#define TKOM_INTERPRETER_LITERAL_H

#include "Assignable.h"
#include "../Token.h"

class Literal : public Assignable{
public:
    explicit Literal() = default;
    Literal(Token token)
    : data(token)
    {

    }

    Type getType() const override {
        return Type::literal;
    }

    Token data;
};


#endif //TKOM_INTERPRETER_LITERAL_H
