#ifndef TKOM_INTERPRETER_PROGRAM_H
#define TKOM_INTERPRETER_PROGRAM_H

#include <vector>
#include <memory>
#include "ASTNode.h"
#include "FunctionDefinition.h"
#include "Statement.h"

class Program : public ASTNode {
public:
    typedef std::shared_ptr<Program> ptr;

    Program() = default;

	Type getType() const override {
		return Type::program;
	}

    void add(FunctionDefinition::ptr functionDefiniton){
        functionDefinitions.push_back(functionDefiniton);
    }

    void add(Statement::ptr statement){
        statements.push_back(statement);
    }

    std::string representation() const override {
        return "Program (" + std::to_string(functionDefinitions.size()) + " function definitions)";
    };

    ChildrenList getChildren() override {
        auto children = ChildrenList(functionDefinitions.begin(), functionDefinitions.end());
        return children;
    }

	std::vector<FunctionDefinition::ptr> functionDefinitions;
	std::vector<Statement::ptr> statements;
};

#endif //TKOM_INTERPRETER_PROGRAM_H