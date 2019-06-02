#ifndef TKOM_INTERPRETER_IREXPRESSION_H
#define TKOM_INTERPRETER_IREXPRESSION_H

#include <memory>
#include "IRAssignable.h"
#include "../Token.h"

class IRExpression : public IRAssignable{
public:
    typedef std::shared_ptr<IRExpression> ptr;

    IRAssignable::ptr first, second;
    Token::Type expressionOperator;

    IRExpression(std::string type, Token::Type oper){
        assignableType = type;
        expressionOperator = oper;
        first = nullptr;
        second = nullptr;
    }

    // todo: execute
};


#endif //TKOM_INTERPRETER_IREXPRESSION_H
