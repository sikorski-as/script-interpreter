#ifndef TKOM_INTERPRETER_BLOCKSTATEMENT_H
#define TKOM_INTERPRETER_BLOCKSTATEMENT_H

#include "Statement.h"

class BlockStatement : public Statement{
public:
    Type getType() const override {
        return Type::block_statement;
    }

    void add(Statement::ptr statement){
        statements.push_back(statement);
    }

    std::vector<Statement::ptr> statements;
};


#endif //TKOM_INTERPRETER_BLOCKSTATEMENT_H
