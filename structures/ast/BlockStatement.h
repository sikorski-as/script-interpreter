#ifndef TKOM_INTERPRETER_BLOCKSTATEMENT_H
#define TKOM_INTERPRETER_BLOCKSTATEMENT_H

#include <vector>
#include "Statement.h"

class BlockStatement : public Statement{
public:
    typedef std::shared_ptr<BlockStatement> ptr;

    Type getType() const override {
        return Type::block_statement;
    }

    void add(Statement::ptr statement){
        statements.push_back(statement);
    }

    std::vector<Statement::ptr> statements;

    std::string representation() const override {
        return "Block statement (" + std::to_string(statements.size()) + " statements)";
    };

    ChildrenList getChildren() override {
        auto children = ChildrenList(statements.begin(), statements.end());
        return children;
    }
};


#endif //TKOM_INTERPRETER_BLOCKSTATEMENT_H
