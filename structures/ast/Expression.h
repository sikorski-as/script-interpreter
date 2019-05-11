#ifndef TKOM_INTERPRETER_EXPRESSION_H
#define TKOM_INTERPRETER_EXPRESSION_H

#include <vector>
#include <initializer_list>
#include "Assignable.h"
#include "../Token.h"

class Expression : public Assignable{
public:
    explicit Expression() = default;

    Expression(Token::Type unaryOperator, Assignable::ptr operand)
    : operators(unaryOperator), operands({operand})
    {

    }

    Expression(Token::Type binaryOperator, std::initializer_list<Assignable::ptr> operands)
    : operators({binaryOperator}), operands(operands)
    {

    }

    Type getType() const override{
        return Type::expression;
    }

    std::vector<Token::Type> operators;
    std::vector<Assignable::ptr> operands;

};


#endif //TKOM_INTERPRETER_EXPRESSION_H
