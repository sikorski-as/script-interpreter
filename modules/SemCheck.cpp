#include "SemCheck.h"
#include <unordered_map>
#include <utility>

void SemCheck::log(SemCheck::LogEntry entry) {
    semCheckLog.push_back(entry);
}

void SemCheck::error(SemCheck::LogEntry entry) {
    log(entry);
    successAchieved = false;
}

bool SemCheck::success() {
    return successAchieved;
}

std::vector<SemCheck::LogEntry> SemCheck::getLog() {
    return semCheckLog;
}

IRProgram::ptr SemCheck::check(Program::ptr syntaxTree) {
    this->syntaxTree = syntaxTree;
    this->definedFunctions.clear();

    for(auto& fun: syntaxTree->functionDefinitions){
        std::string fname = fun->functionName;
        if(StdLib::hasFunction(fname)){
            error({std::string("Function with name ") + fname + " already exists in stdlib"});
            continue;
        }

        if(definedFunctions.count(fname)){
            error({std::string("Function with name ") + fname + " already defined"});
            continue;
        }

        definedFunctions[fname] = checkFunctionDefinition(fun);
    }

    // todo: create IRProgram here
    //return executableProgram;

    return nullptr;
}

IRFunction::ptr SemCheck::checkFunctionDefinition(FunctionDefinition::ptr fundef) {
    auto ir_fun = std::make_shared<IRFunction>();
    log({"Checking function definition..."});

    currentFunctionName = fundef->functionName;
    currentFunctionReturnType = fundef->returnTypeName;

    auto context = ContextPrototype(); // todo: add stdlib functions to scope???
    for(auto& varproto: fundef->arguments){
        if(context.isVariableInScope(varproto.second)){
            error({std::string("Variable " + varproto.second + " already defined in this scope")});
        }
        else {
            if(StdLib::hasType(varproto.first)){
                context.addVariable(varproto);
            }
            else{
                error({std::string("Unknown type '" + varproto.second + "'" )});
            }
        }
    }

    if(fundef->returnTypeName == "void")
        context.returnStatementSpotted();

    // check statements inside function's body
    ir_fun->statements = checkStatements(context, fundef->body);

    if(!context.hasReturnStatement()){
        error({std::string("No return statement in a function returning non-void (") + fundef->getTypeAndName() + ")"});
    }

    ir_fun->functionName = fundef->functionName;
    ir_fun->returnTypeName = fundef->returnTypeName;
    ir_fun->contextProto = context;

    return ir_fun;
}

IRStatement::StatementsList SemCheck::checkStatements(ContextPrototype & context, BlockStatement::ptr block) {
    IRStatement::StatementsList statements;
    for(auto& s: block->statements){
        statements.push_back(checkStatement(context, s));
    }
    return statements;
}

IRStatement::ptr SemCheck::checkStatement(ContextPrototype & context, Statement::ptr statement) {
    auto type = statement->getType();

    switch(type){
        case ASTNode::Type::if_statement:
            return checkIfStatement(context, statement);
        case ASTNode::Type::while_statement:
            return checkWhileStatement(context, statement);
        case ASTNode::Type::var_declaration:
            return checkVarDeclaration(context, statement);
        case ASTNode::Type::var_definition:
            return checkVarDefinition(context, statement);
        case ASTNode::Type::var_assignment:
            return checkVarAssignment(context, statement);
        case ASTNode::Type::return_statement:
            return checkReturnStatement(context, statement);
        case ASTNode::Type::function_call:
            log({"Function call statement: todo"});
            return nullptr;
        case ASTNode::Type::method_call:
            log({"Method call statement: todo"});
            return nullptr;
    }

    error({"Fatal error: unknown type of statement"});
    return nullptr;
}

IRAssignable::ptr SemCheck::checkAssignable(ContextPrototype& context, Assignable::ptr assignable) {
    return nullptr; // todo
}

IRStatement::ptr SemCheck::checkIfStatement(ContextPrototype& context, Statement::ptr statement) {
    auto if_statement = std::dynamic_pointer_cast<IfStatement>(statement);

    auto condition = checkAssignable(context, if_statement->condition);
    if(condition->getType() != "bool"){
        error({"If statement's condition must evaluate to boolean"});
    }

    auto true_block_context = ContextPrototype(&context);
    auto true_block = checkStatements(true_block_context, if_statement->trueBlock);

    auto false_block_context = ContextPrototype(&context);
    auto false_block = checkStatements(false_block_context, if_statement->falseBlock);

    return std::make_shared<IRIfStatement>(condition, true_block, false_block);
}

IRStatement::ptr SemCheck::checkWhileStatement(ContextPrototype & context, Statement::ptr statement) {
    auto while_statement = std::dynamic_pointer_cast<WhileStatement>(statement);

    auto condition = checkAssignable(context, while_statement->condition);
    if(condition->getType() != "bool"){
        error({"While statement's condition must evaluate to boolean"});
    }

    auto new_context = ContextPrototype(&context);
    auto body = checkStatements(new_context, while_statement->body);

    return std::make_shared<IRWhileStatement>(condition, body);
}

IRStatement::ptr SemCheck::checkVarDeclaration(ContextPrototype& context, Statement::ptr statement) {
    auto declaration = std::dynamic_pointer_cast<VariableDeclaration>(statement);
    if(context.isVariableInScope(declaration->name)){
        error({std::string("Variable '" + declaration->name + "' already declared in this scope")});
    }
    else{
        if(!StdLib::hasType(declaration->typeName)){
            error({std::string("Declaration of variable of an unknown type (" + declaration->typeName + ")")});
        }
        else{
            auto varproto = std::make_pair(declaration->typeName, declaration->name);
            context.addVariable(varproto);

            return std::make_shared<IRVarDeclaration>(declaration->typeName, declaration->name);
        }
    }

    return nullptr;
}

IRStatement::ptr SemCheck::checkVarDefinition(ContextPrototype& context, Statement::ptr statement) {
    auto definition = std::dynamic_pointer_cast<VariableDefinition>(statement);
    if(context.isVariableInScope(definition->name)){
        error({std::string("Variable '" + definition->name + "' already declared in this scope")});
    }
    else{
        if(!StdLib::hasType(definition->typeName)){
            error({std::string("Declaration of variable of an unknown type (" + definition->typeName + ")")});
        }
        else{
            auto assignable = checkAssignable(context, definition->value);
            auto var_type = definition->typeName;
            auto assign_type = assignable->getType();

            if(var_type != assign_type){
                error({std::string("Incompatible types for assignment ('" + definition->name +
                                   "' is of type '" + var_type + "', not '" + assign_type + "')")});
            }
            else{
                auto varproto = std::make_pair(definition->typeName, definition->name);
                context.addVariable(varproto);

                return std::make_shared<IRVarDefinition>(definition->typeName, definition->name, assignable);
            }
        }
    }

    return nullptr;
}

IRStatement::ptr SemCheck::checkVarAssignment(ContextPrototype& context, Statement::ptr statement) {
    auto assignment = std::dynamic_pointer_cast<VariableAssignment>(statement);
    if(!context.isVariableInScope(assignment->name)){
        error({std::string("Variable '" + assignment->name + "' not declared in this scope")});
    }
    else{
        auto assignable = checkAssignable(context, assignment->value);
        auto var_type = context.getVariableType(assignment->name);
        auto assign_type = assignable->getType();

        if(var_type != assign_type){
            error({std::string("Incompatible types for assignment ('" + assignment->name +
                "' is of type '" + var_type + "', not '" + assign_type + "')")});
        }
        else{
            return std::make_shared<IRVarAssignment>(assignment->name, assignable);
        }
    }

    return nullptr;
}

IRStatement::ptr SemCheck::checkReturnStatement(ContextPrototype& context, Statement::ptr statement) {
    auto return_statement = std::dynamic_pointer_cast<ReturnStatement>(statement);

    auto assignable = checkAssignable(context, return_statement->returnedValue);
    auto ret_value_type = assignable->getType();
    context.returnStatementSpotted();

    if(currentFunctionReturnType != ret_value_type){
        error({std::string("Incompatible types for return ('" + currentFunctionName +
                           "' is declared to return '" + currentFunctionReturnType +
                           "', not '" + ret_value_type + "')")});
    }
    else{
        return std::make_shared<IRReturnStatement>(assignable);
    }

    return nullptr;
}
