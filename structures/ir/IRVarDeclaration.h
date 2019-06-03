#ifndef TKOM_INTERPRETER_IRVARDECLARATION_H
#define TKOM_INTERPRETER_IRVARDECLARATION_H

#include <string>
#include "IRStatement.h"
#include "IRObject.h"

class IRVarDeclaration : public IRStatement{
    std::string typeName, name;
public:
    IRVarDeclaration(std::string& type_name, std::string& variable_name){
        typeName = type_name;
        name = variable_name;
    }

    IRObject::ptr execute(IRContext* context) override {
        debug("Executing declaration of variable " + name);

        auto object = std::make_shared<IRObject>();
        object->type = typeName;

        if(typeName == "bool"){
            object->value = false;
        }
        else if(typeName == "int"){
            object->value = 0;
        }
        else if(typeName == "float"){
            object->value = 0.0f;
        }
        else if(typeName == "string"){
            object->value = std::string("");
        }

        context->addSymbol(name, object);

        return nullptr;
    }
};


#endif //TKOM_INTERPRETER_IRVARDECLARATION_H
