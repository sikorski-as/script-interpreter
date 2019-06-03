#ifndef TKOM_INTERPRETER_IREXPRESSION_H
#define TKOM_INTERPRETER_IREXPRESSION_H

#include <memory>
#include <variant>
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

    IRObject::ptr execute(IRContext* context) override{
        using tt = Token::Type;
        if(second == nullptr){ // unary not
            if(expressionOperator == tt::operator_not){
                auto object = first->execute(context);
                auto boolean = !std::get<bool>(object->value);
                object->value = boolean;
                return object;
            }
        }
        else{
            if(expressionOperator == tt::operator_concat){
                auto object1 = first->execute(context);
                auto object2 = second->execute(context);
                std::string combined = std::get<std::string>(object1->value) + std::get<std::string>(object2->value);
                auto object = std::make_shared<IRObject>();
                object->type = "string";
                object->value = combined;

                return object;
            }
            else if(expressionOperator == tt::operator_less){
//                auto object = std::make_shared<IRObject>();
//                object->type = "bool";
//                object->value =
            }
        }

        return nullptr;
    }
};


#endif //TKOM_INTERPRETER_IREXPRESSION_H
