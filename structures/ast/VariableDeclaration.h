#ifndef TKOM_INTERPRETER_VARIABLEDECLARATION_H
#define TKOM_INTERPRETER_VARIABLEDECLARATION_H

#include <string>
#include "Statement.h"

class VariableDeclaration : public Statement{
public:
    VariableDeclaration(std::string name, std::string typeName)
    : name(name), typeName(typeName)
    {

    }

    Type getType() const override {
        return Type::var_declaration;
    }

    std::string representation() const override {
        return "Variable " + name + " declaration of type " + typeName;
    };

    std::string name;
    std::string typeName;
};


#endif //TKOM_INTERPRETER_VARIABLEDECLARATION_H
