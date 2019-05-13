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

    Type getType() const override {
        return Type::function_definition;
    }

    std::string representation() const override {
        return "Definition of function "
        + returnTypeName + " " + functionName + "([" + std::to_string(arguments.size()) + "])";
    };

    ChildrenList getChildren() override {
        auto children = ChildrenList({body});
        return children;
    }

    std::string returnTypeName;
    std::string functionName;
    ArgumentsListPrototype arguments;
    BlockStatement::ptr body;
};


#endif //TKOM_INTERPRETER_FUNCTIONDEFINITION_H
