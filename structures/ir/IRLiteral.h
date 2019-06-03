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

    IRObject::ptr execute(IRContext*) override{
        auto dtype = literal->getDataType();
        auto object = std::make_shared<IRObject>();

        if(dtype == "bool" || dtype == "int" || dtype == "float" || dtype == "string"){
            object->value = literal->data.value;
        }

        object->type = dtype;
        return object;
    }
};

#endif //TKOM_INTERPRETER_IRLITERAL_H
