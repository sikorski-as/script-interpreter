#ifndef TKOM_INTERPRETER_IRLITERAL_H
#define TKOM_INTERPRETER_IRLITERAL_H

#include <memory>
#include "IRAssignable.h"
#include "IRObject.h"
#include "../ast/Literal.h"

class IRLiteral : public IRAssignable{
public:
    typedef std::shared_ptr<IRLiteral> ptr;

    Literal::ptr literal;

    IRLiteral(Literal::ptr literal){
        this->literal = literal;
    }

    std::string getType() override {
        return literal->getDataType();
    }

    // todo: execute
};

#endif //TKOM_INTERPRETER_IRLITERAL_H
