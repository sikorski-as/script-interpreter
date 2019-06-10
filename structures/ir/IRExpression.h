#ifndef TKOM_INTERPRETER_IREXPRESSION_H
#define TKOM_INTERPRETER_IREXPRESSION_H

#include <memory>
#include <variant>
#include <string>
#include "IRAssignable.h"
#include "../Token.h"

class IRExpression : public IRAssignable{
public:
    typedef std::shared_ptr<IRExpression> ptr;

    IRAssignable::ptr first, second;
    Token::Type expressionOperator;

    class ZeroDivision {
        std::string reason;
    };

    IRExpression(std::string type, Token::Type oper){
        assignableType = type;
        expressionOperator = oper;
        first = nullptr;
        second = nullptr;
    }

    IRObject::ptr execute(IRContext* context) override{
        debug("Evaluating expression");
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
            auto object1 = first->execute(context);
            auto object2 = second->execute(context);
            auto object = std::make_shared<IRObject>();

            if(expressionOperator == tt::operator_concat){
                std::string combined = std::get<std::string>(object1->value) + std::get<std::string>(object2->value);
                object->type = "string";
                object->value = combined;

                return object;
            }
            else if(expressionOperator == tt::operator_equal){
                object->type = "bool";
                object->value = object1->value == object2->value;
                return object;
            }
            else if(expressionOperator == tt::operator_not_equal){
                object->type = "bool";
                object->value = object1->value != object2->value;
                return object;
            }
            else if(expressionOperator == tt::operator_less){
                object->type = "bool";
                if(first->getType() == "int"){
                    object->value = std::get<int>(object1->value) < std::get<int>(object2->value);
                    return object;
                }
                else if(first->getType() == "float"){
                    object->value = std::get<float>(object1->value) < std::get<float>(object2->value);
                    return object;
                }
                return nullptr;
            }
            else if(expressionOperator == tt::operator_less_equal){
                object->type = "bool";
                if(first->getType() == "int"){
                    object->value = std::get<int>(object1->value) <= std::get<int>(object2->value);
                    return object;
                }
                else if(first->getType() == "float"){
                    object->value = std::get<float>(object1->value) <= std::get<float>(object2->value);
                    return object;
                }
                return nullptr;
            }
            else if(expressionOperator == tt::operator_greater){
                object->type = "bool";
                if(first->getType() == "int"){
                    object->value = std::get<int>(object1->value) > std::get<int>(object2->value);
                    return object;
                }
                else if(first->getType() == "float"){
                    object->value = std::get<float>(object1->value) > std::get<float>(object2->value);
                    return object;
                }
                return nullptr;
            }
            else if(expressionOperator == tt::operator_greater_equal){
                object->type = "bool";
                if(first->getType() == "int"){
                    object->value = std::get<int>(object1->value) >= std::get<int>(object2->value);
                    return object;
                }
                else if(first->getType() == "float"){
                    object->value = std::get<float>(object1->value) >= std::get<float>(object2->value);
                    return object;
                }
                return nullptr;
            }
            /*
             *  arithmetic operators
             */
            else if(expressionOperator == tt::operator_plus){
                object->type = object1->type;
                if(first->getType() == "int"){
                    object->value = std::get<int>(object1->value) + std::get<int>(object2->value);
                    return object;
                }
                else if(first->getType() == "float"){
                    object->value = std::get<float>(object1->value) + std::get<float>(object2->value);
                    return object;
                }
                return object;
            }
            else if(expressionOperator == tt::operator_minus){
                object->type = object1->type;
                if(first->getType() == "int"){
                    object->value = std::get<int>(object1->value) - std::get<int>(object2->value);
                    return object;
                }
                else if(first->getType() == "float"){
                    object->value = std::get<float>(object1->value) - std::get<float>(object2->value);
                    return object;
                }
                return object;
            }
            else if(expressionOperator == tt::operator_multiply){
                object->type = object1->type;
                if(first->getType() == "int"){
                    object->value = std::get<int>(object1->value) * std::get<int>(object2->value);
                    return object;
                }
                else if(first->getType() == "float"){
                    object->value = std::get<float>(object1->value) * std::get<float>(object2->value);
                    return object;
                }
                return object;
            }
            else if(expressionOperator == tt::operator_divide){
                object->type = object1->type;
                if(first->getType() == "int"){
                    int second = std::get<int>(object2->value);
                    if(second == 0)
                        throw RuntimeError("Runtime error: dividing by zero");
                    object->value = std::get<int>(object1->value) / second;
                    return object;
                }
                else if(first->getType() == "float"){
                    object->value = std::get<float>(object1->value) / std::get<float>(object2->value);
                    return object;
                }
                return object;
            }
        }

        return nullptr;
    }
};


#endif //TKOM_INTERPRETER_IREXPRESSION_H
