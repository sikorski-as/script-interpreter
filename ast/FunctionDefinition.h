#ifndef TKOM_INTERPRETER_FUNCTIONDEFINITION_H
#define TKOM_INTERPRETER_FUNCTIONDEFINITION_H

#include <string>
#include <vector>
#include "ASTNode.h"
#include "BlockStatement.h"

class FunctionDefinition : public ASTNode{
public:
    typedef std::shared_ptr<FunctionDefinition> ptr;
    typedef std::vector<std::pair<std::string, std::string>> ArgumentsListPrototype;

    explicit FunctionDefinition() = default;

    FunctionDefinition(std::string returnedTypeName,
                       std::string functionName,
                       ArgumentsListPrototype arguments,
                       BlockStatement::ptr body)
            : returnTypeName(returnedTypeName), functionName(functionName), arguments(arguments),  body(body)
    {

    }

//    FunctionDefinition(std::string returnedTypeName,
//                       std::string functionName,
//                       std::initializer_list<std::pair<std::string, std::string>> arguments = {},
//                       BlockStatement::ptr body = nullptr)
//            : returnTypeName(returnedTypeName), functionName(functionName), arguments(arguments),  body(body)
//    {
//
//    }

    Type getType() const override {
        return Type::function_definition;
    }

    std::string returnTypeName;
    std::string functionName;
    ArgumentsListPrototype arguments;
    BlockStatement::ptr body;
};


#endif //TKOM_INTERPRETER_FUNCTIONDEFINITION_H
