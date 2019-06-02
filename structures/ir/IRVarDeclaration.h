#ifndef TKOM_INTERPRETER_IRVARDECLARATION_H
#define TKOM_INTERPRETER_IRVARDECLARATION_H

#include <string>
#include "IRStatement.h"

class IRVarDeclaration : public IRStatement{
    std::string typeName, name;
public:
    IRVarDeclaration(std::string& type_name, std::string& variable_name){
        typeName = type_name;
        name = variable_name;
    }

    // todo: execute()
};


#endif //TKOM_INTERPRETER_IRVARDECLARATION_H
