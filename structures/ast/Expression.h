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
    : operators({unaryOperator}), operands({operand})
    {

    }

    Expression(Token::Type binaryOperator, std::initializer_list<Assignable::ptr> operands)
    : operators({binaryOperator}), operands(operands)
    {

    }

    Type getType() const override{
        return Type::expression;
    }

    void addOperator(Token::Type operatorType){
        operators.push_back(operatorType);
    }

    void addOperand(Assignable::ptr operand){
        operands.push_back(operand);
    }

    std::string representation() const override {
        if(operators.size() == 1){
            if(operands.size() == 1){
                return "Expression (unary)";
            }
            else if(operands.size() == 2){
                return "Expression (binary)";
            }
        }
        else if (operators.size() == 2){
            return "Expression (ternary)";
        }

        return "Expression (number of operators: " + std::to_string(operators.size()) + ")";
    };

    ChildrenList getChildren() override {
        auto children = ChildrenList(operands.begin(), operands.end());
        return children;
    }

    std::vector<Token::Type> operators;
    std::vector<Assignable::ptr> operands;
};


#endif //TKOM_INTERPRETER_EXPRESSION_H
