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
    this->successAchieved = true;
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

    if(definedFunctions.count("main") == 0){
        error({"Entry point of execution (a.k.a. 'main' function) is not defined"});
    }
    else if(definedFunctions.at("main")->returnTypeName != "void"){
        error({"Entry point of execution (a.k.a. 'main' function) should return nothing"});
    }
    else if(!definedFunctions.at("main")->contextProto.functionArgsOrder.empty()){
        error({"Entry point of execution (a.k.a. 'main' function) should not take any arguments"});
    }

    auto program = std::make_shared<IRProgram>();
    program->definedFunctions = definedFunctions;

    return program;
}

IRFunction::ptr SemCheck::checkFunctionDefinition(FunctionDefinition::ptr fundef) {
    auto ir_fun = std::make_shared<IRFunction>();
    //log({"Checking function definition..."});

    currentFunctionName = fundef->functionName;
    currentFunctionReturnType = fundef->returnTypeName;
    currentFunctionParamsPrototype.clear();

    auto context = ContextPrototype();
    auto new_context = ContextPrototype(&context);

    for(auto& varproto: fundef->arguments){
        if(context.isVariableInScope(varproto.second)){
            error({std::string("Variable " + varproto.second + " already defined in this scope")});
        }
        else {
            if(StdLib::hasType(varproto.first)){
                context.addVariable(varproto);
                currentFunctionParamsPrototype.push_back(varproto);
            }
            else{
                error({std::string("Unknown type '" + varproto.second + "'" )});
            }
        }
    }

    if(fundef->returnTypeName == "void")
        context.returnStatementSpotted();

    // check statements inside function's body
    ir_fun->statements = checkStatements(new_context, fundef->body);

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
            return checkFunctionCall(context, statement);
        case ASTNode::Type::method_call:
            log({"Method call statement: todo"});
            return nullptr;
    }

    error({"Fatal error: unknown type of statement"});
    return nullptr;
}

IRStatement::ptr SemCheck::checkIfStatement(ContextPrototype& context, Statement::ptr statement) {
    auto if_statement = std::dynamic_pointer_cast<IfStatement>(statement);

    auto condition = checkAssignable(context, if_statement->condition);

    if(condition != nullptr && condition->getType() != "bool"){
        error({"If statement's condition must evaluate to boolean"});
        return nullptr;
    }

    auto true_block_context = ContextPrototype(&context);
    auto true_block = checkStatements(true_block_context, if_statement->trueBlock);

    auto false_block_context = ContextPrototype(&context);
    IRStatement::StatementsList false_block;
    if(if_statement->falseBlock){
        false_block = checkStatements(false_block_context, if_statement->falseBlock);
    }

    return std::make_shared<IRIfStatement>(condition, true_block, false_block);
}

IRStatement::ptr SemCheck::checkWhileStatement(ContextPrototype & context, Statement::ptr statement) {
    auto while_statement = std::dynamic_pointer_cast<WhileStatement>(statement);

    auto condition = checkAssignable(context, while_statement->condition);

    if(condition != nullptr && condition->getType() != "bool"){
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
            if(assignable == nullptr){
                return nullptr;
            }
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
        if(assignable == nullptr){
            return nullptr;
        }
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
    if(assignable == nullptr){
        return nullptr;
    }
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

IRFunctionCall::ptr SemCheck::checkFunctionCall(ContextPrototype& context, ASTNode::ptr statement) {
    auto funcall = std::dynamic_pointer_cast<FunctionCall>(statement);
    auto fun_name = funcall->functionName;

    if(definedFunctions.count(fun_name) > 0){
        //log({"already defined function"});

        //auto& defined_function_context = definedFunctions[fun_name]->contextProto;
        auto& defined_function_args = definedFunctions[fun_name]->contextProto.functionArgsOrder;
        auto& fun_args = funcall->arguments;

        if(fun_args.size() != defined_function_args.size()){
            error({std::string("Number of arguments for call of function '" + fun_name +
                               "' differs from the one defined before")});
            return nullptr;
        }
        else{
            auto functionCall = std::make_shared<IRFunctionCall>(fun_name);

            for(int i = 0; i < fun_args.size(); i++){
                auto assignable = checkAssignable(context, fun_args[i]);
                if(assignable && assignable->getType() != defined_function_args[i].first){
                    error({std::string("Incorrect type ('" + assignable->getType()
                                       + "') for function call (expected '" + defined_function_args[i].first + "'")});
                    return nullptr;
                }
                functionCall->addArgument(assignable);
            }
            functionCall->returnType = definedFunctions[fun_name]->returnTypeName;
            //log({"Successfully parsed function call (1)"});
            return functionCall;
        }
    }
    else if(currentFunctionName == fun_name){
        auto& defined_function_args = currentFunctionParamsPrototype;
        auto& fun_args = funcall->arguments;

        if(fun_args.size() != defined_function_args.size()){
            error({std::string("Number of arguments for call of function '" + fun_name +
                               "' differs from the one defined before")});
            return nullptr;
        }
        else{
            auto functionCall = std::make_shared<IRFunctionCall>(fun_name);

            for(int i = 0; i < fun_args.size(); i++){
                auto assignable = checkAssignable(context, fun_args[i]);
                if(assignable && assignable->getType() != defined_function_args[i].first){
                    error({std::string("Incorrect type ('" + assignable->getType()
                                       + "') for function call (expected '" + defined_function_args[i].first + "'")});
                    return nullptr;
                }
                functionCall->addArgument(assignable);
            }
            functionCall->returnType = currentFunctionReturnType;
            //log({"Successfully parsed function call (2)"});
            return functionCall;
        }
    }
    else{
        if(StdLib::hasFunction(fun_name)){
            auto& std_fun_args = StdLib::STDLIB_FUNCTIONS[fun_name];
            auto& fun_args = funcall->arguments;

            auto functionCall = std::make_shared<IRFunctionCall>(fun_name);

            if(fun_args.size() != std_fun_args.size() - 2){ // minus name and return type
                error({std::string("Number of arguments for call of function '" + fun_name +
                "' differs from the one in the standard library")});
                return nullptr;
            }
            else{
                for(int i = 0; i < fun_args.size(); i++){
                    auto assignable = checkAssignable(context, fun_args[i]);
                    if(assignable && assignable->getType() != std_fun_args[i + 2]){ // because arguments types begin at index 2
                        error({std::string("Incorrect type ('" + assignable->getType()
                        + "') for function call (expected '" + std_fun_args[i + 2] + "'")});
                        return nullptr;
                    }

                    functionCall->addArgument(assignable);
                }

                functionCall->returnType = std_fun_args[0];

                //log({"Successfully parsed function call (2)"});
                return functionCall;
            }
        }
    }

    error({std::string("Usage of undefined function '" + fun_name + "'")});
    return nullptr;
}

IRAssignable::ptr SemCheck::checkAssignable(ContextPrototype& context, Assignable::ptr assignable) {
    auto type = assignable->getType();

    switch(type){
        case ASTNode::Type::literal:
            return checkLiteral(context, assignable);

        case ASTNode::Type::variable:
            return checkVariable(context, assignable);

        case ASTNode::Type::expression:
            return checkExpression(context, assignable);

        case ASTNode::Type::function_call:
            return checkFunctionCall(context, assignable);

        case ASTNode::Type::method_call:
            break;
    }

    error({"Unknown type of R-value"});

    return nullptr;
}

IRAssignable::ptr SemCheck::checkLiteral(ContextPrototype& context, Assignable::ptr assignable) {
    auto literal = std::dynamic_pointer_cast<Literal>(assignable);

    return std::make_shared<IRLiteral>(literal);
}

IRAssignable::ptr SemCheck::checkVariable(ContextPrototype& context, Assignable::ptr assignable) {
    auto variable = std::dynamic_pointer_cast<Variable>(assignable);

    if(context.isVariableInScope(variable->name)){
        std::string vartype = context.getVariableType(variable->name);
        return std::make_shared<IRVariable>(vartype, variable->name);
    }
    else{
        error({"Variable '" + variable->name + "' undeclared in this scope"});
    }

    return nullptr;
}

IRAssignable::ptr SemCheck::checkExpression(ContextPrototype& context, Assignable::ptr assignable) {
    using ttype = Token::Type;
    auto expression = std::dynamic_pointer_cast<Expression>(assignable);
    auto& operators = expression->operators;
    auto& operands = expression->operands;

    if(operators.size() == 1){
        auto oper = operators[0];

        if(operands.size() == 1){
           if(oper == ttype::operator_not){
               auto expr = std::make_shared<IRExpression>("bool", oper);
               auto operand = checkAssignable(context, operands[0]);
               expr->first = operand;

               if(operand != nullptr && operand->getType() == "bool")
                   return expr;
               else{
                   error({"Unary not requires 'bool' as operand, '" + operand->getType() + "' given"});
                   return nullptr;
               }
           }
           error({"Operator 'not' must be unary"});
           return nullptr;
        }
        else if(operands.size() == 2){
            auto expr = std::make_shared<IRExpression>("none", oper);
            auto first = checkAssignable(context, operands[0]);
            auto second = checkAssignable(context, operands[1]);
            expr->first = first;
            expr->second = second;

            // operatory logiczne - operandy mogą być tylko bool
            if(oper == ttype::operator_and || oper == ttype::operator_or){
                if(checkTypesPair(first, second, "bool", "bool")) {
                    expr->assignableType = "bool";
                }
                error({"Logical operator requires 'bool' type as operands"});
                return nullptr;
            }

            // operatory relacyjne - operandy mogą być liczbami dla wszystkich lub bool dla ==, !=
            if(oper == ttype::operator_equal || oper == ttype::operator_not_equal){
                if(checkTypesPair(first, second, "int", "int")
                    || checkTypesPair(first, second, "float", "float")
                       || checkTypesPair(first, second, "bool", "bool")
                          || checkTypesPair(first, second, "string", "string")){

                    expr->assignableType = "bool";
                    return expr;
                }

                error({"Comparison operator requires two identical numeric types, bool type or string type as operands"});
                return nullptr;
            }
            else if(oper == ttype::operator_less
                || oper == ttype::operator_less_equal
                || oper == ttype::operator_greater
                || oper == ttype::operator_greater_equal){

                if(checkTypesPair(first, second, "int", "int") || checkTypesPair(first, second, "float", "float")){
                    expr->assignableType = "bool";
                    return expr;
                }

                error({"Comparison operator requires two identical numeric types as operands"});
                return nullptr;
            }

            // operatory arytmetyczne - operandy mogą być tylko liczbami
            if(oper == ttype::operator_minus
                || oper == ttype::operator_plus
                || oper == ttype::operator_divide
                || oper == ttype::operator_multiply){

                if(checkTypesPair(first, second, "int", "int")){
                    expr->assignableType = "int";
                    return expr;
                }
                else if(checkTypesPair(first, second, "float", "float")){
                    expr->assignableType = "float";
                    return expr;
                }

                error({"Arithmetic operator requires two identical numeric types as operands"});
                return nullptr;
            }

            // operator konkatenacji - operandy mogą być tylko string
            if(oper == ttype::operator_concat){
                if(checkTypesPair(first, second, "string", "string")){
                    expr->assignableType = "string";
                    return expr;
                }
                else{
                    error({"Concatenation operator requires two strings as operands"});
                    return nullptr;
                }
            }

            error({"Expression of incorrect operands"});
            return nullptr;
        }
    }

    error({"Fatal error: expression of an unknown hierarchy"});
    return nullptr;
}

bool SemCheck::checkTypesPair(IRAssignable::ptr first, IRAssignable::ptr second, std::string firstType, std::string secondType) {
    if(first != nullptr && second != nullptr){
        if(first->getType() ==  firstType && second->getType() == secondType){
            return true;
        }
    }
    return false;
}
