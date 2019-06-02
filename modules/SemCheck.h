#ifndef TKOM_INTERPRETER_SEMCHECK_H
#define TKOM_INTERPRETER_SEMCHECK_H

#include <unordered_map>
#include <vector>

#include "StdLib.h"
#include "../structures/ast/AST.h"
#include "../structures/ir/IR.h"

class SemCheck {
public:
    struct LogEntry{
        std::string text = "";
        int line = 0, column = 0;
        bool tokenInfo = false;
    };
    struct Exception{std::string reason;};
    bool success();
    std::vector<LogEntry> getLog();

    IRProgram::ptr check(Program::ptr);
private:
    Program::ptr syntaxTree;
    IRProgram::ptr executableProgram;
    std::unordered_map<std::string, IRFunction::ptr> definedFunctions;

    std::vector<LogEntry> semCheckLog;
    bool successAchieved = false;
    void log(LogEntry);
    void error(LogEntry);

    std::string currentFunctionName;
    std::string currentFunctionReturnType;

    IRFunction::ptr checkFunctionDefinition(FunctionDefinition::ptr);

    IRStatement::StatementsList checkStatements(ContextPrototype&, BlockStatement::ptr);
    IRStatement::ptr checkStatement(ContextPrototype&, Statement::ptr);

    IRAssignable::ptr checkAssignable(ContextPrototype&, Assignable::ptr); // todo!

    IRStatement::ptr checkIfStatement(ContextPrototype&, Statement::ptr);
    IRStatement::ptr checkWhileStatement(ContextPrototype&, Statement::ptr);
    IRStatement::ptr checkVarDeclaration(ContextPrototype&, Statement::ptr);
    IRStatement::ptr checkVarDefinition(ContextPrototype&, Statement::ptr);
    IRStatement::ptr checkVarAssignment(ContextPrototype&, Statement::ptr);
    IRStatement::ptr checkReturnStatement(ContextPrototype&, Statement::ptr);

    IRStatement::ptr checkFunctionCall(ContextPrototype&, Statement::ptr);

};

#endif //TKOM_INTERPRETER_SEMCHECK_H
