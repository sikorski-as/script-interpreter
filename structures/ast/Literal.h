#ifndef TKOM_INTERPRETER_LITERAL_H
#define TKOM_INTERPRETER_LITERAL_H

#include <memory>
#include "Assignable.h"
#include "../Token.h"

class Literal : public Assignable{
public:
    typedef std::shared_ptr<Literal> ptr;

    explicit Literal() = default;
    Literal(Token token)
    : data(token)
    {

    }

    Type getType() const override {
        return Type::literal;
    }

    std::string representation() const override {
        std::string repr;
        if(data.type == Token::Type::const_int){
            repr = "Int literal: " + std::to_string(std::get<int>(data.value));
        }
        else if(data.type == Token::Type::const_float){
            repr = "Float literal: " + std::to_string(std::get<float>(data.value));
        }
        else if(data.type == Token::Type::const_string){
            repr = "String literal: '" + std::get<std::string>(data.value) + "'";
        }
        else{
            repr = "Boolean literal ";
            repr += data.type == Token::Type::keyword_true ? "true" : "false";
        }
        return repr;
    };

    ChildrenList getChildren() override {
        auto children = ChildrenList();
        return children;
    }

    Token data;

    std::string getDataType(){
        if(std::holds_alternative<bool>(data.value)){
            return "bool";
        }
        else if(std::holds_alternative<int>(data.value)){
            return "int";
        }
        else if(std::holds_alternative<float>(data.value)){
            return "float";
        }
        else if(std::holds_alternative<std::string>(data.value)){
            return "string";
        }

        return "none";
    }
};


#endif //TKOM_INTERPRETER_LITERAL_H
