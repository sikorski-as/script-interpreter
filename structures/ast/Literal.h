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
            repr = "Boolean literal";
        }
        return repr;
    };

    ChildrenList getChildren() override {
        auto children = ChildrenList();
        return children;
    }

    Token data;
};


#endif //TKOM_INTERPRETER_LITERAL_H
