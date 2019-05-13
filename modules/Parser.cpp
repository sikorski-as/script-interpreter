#include "Parser.h"
#include <iostream>

//
// public
//

Parser::Parser(Lexer & lexer)
        : lexer(lexer), successAchieved(false)
{

}

Program::ptr Parser::parse() {
    successAchieved = true;
    auto program = std::make_shared<Program>();

    try{
        while(getToken().type != Token::Type::eof){
            /*parseAssignable();*/
            auto fundef = parseFunctionDefinition();
            if(fundef != nullptr){
                program->add(fundef);
            }
        }
    }
    catch(UnexpectedEndOfFile& e){
        auto t = getToken();
        error({e.what(), t.line, t.column, true});
    }
    catch(Lexer::LexerException& e){
        error({e.what()});
    }

    if(successAchieved){
        return program;
    }
    else{
        return nullptr;
    }
}

bool Parser::success() {
    return successAchieved;
}

std::vector<Parser::LogEntry> Parser::getLog() {
    return parserLog;
}

//
// private
//

Token Parser::consumeToken() {
    lexer.consumeToken();
    return lexer.getToken();
}

Token Parser::getToken() {
    return lexer.getToken();
}

Token Parser::getAndConsumeToken() {
    auto t = getToken();
    consumeToken();
    return t;
}

void Parser::log(Parser::LogEntry entry) {
    parserLog.push_back(entry);
}

void Parser::error(Parser::LogEntry entry) {
    log(entry);
    successAchieved = false;
}

void Parser::errorWithTokenInfo(std::string message){
    auto t = getToken();
    error({message, t.line, t.column, true});
}

bool Parser::accept(const std::initializer_list<Token::Type> & acceptableTokenTypes) {
    bool eofTokenTypeInList = false;
    auto tokenType = getToken().type;

    for(auto& acceptableTokenType: acceptableTokenTypes){
        if(acceptableTokenType == Token::Type::eof){
            eofTokenTypeInList = true;
        }

        if(tokenType == acceptableTokenType){
            return true;
        }
    }

    if(!eofTokenTypeInList && tokenType == Token::Type::eof)
        throw UnexpectedEndOfFile();

    return false;
}

bool Parser::accept(Token::Type acceptableTokenType) {
    return accept({acceptableTokenType});
}

bool Parser::acceptOrErrorWithTokenInfo(Token::Type acceptableTokenType, std::string errorMessage) {
    try{
        auto success = accept(acceptableTokenType);
        if(!success)
            errorWithTokenInfo(errorMessage);
        return success;
    }
    catch(UnexpectedEndOfFile&){
        errorWithTokenInfo(errorMessage);
        throw UnexpectedEndOfFile();
    }
}

bool Parser::acceptOrErrorWithTokenInfo(const std::initializer_list<Token::Type>& acceptableTokenTypes, std::string errorMessage) {
    try{
        auto success = accept(acceptableTokenTypes);
        if(!success)
            errorWithTokenInfo(errorMessage);
        return success;
    }
    catch(UnexpectedEndOfFile&){
        errorWithTokenInfo(errorMessage);
        throw UnexpectedEndOfFile();
    }
}

std::string Parser::getIdentifierNameOrErrorWithTokenInfo(std::string message) {
    if(accept(Token::Type::identifier)){
        return std::get<std::string>(getToken().value);
    }
    else{
        errorWithTokenInfo(message);
        return std::string();
    }
}

FunctionDefinition::ptr Parser::parseFunctionDefinition() {
    debug("Parsing function definition");
    auto functionDefinition = std::make_shared<FunctionDefinition>();

    // get returned type
    functionDefinition->returnTypeName =
            getIdentifierNameOrErrorWithTokenInfo("Expected a type-specifier for a function definition");
    consumeToken();

    // get function name
    functionDefinition->functionName =
            getIdentifierNameOrErrorWithTokenInfo("Expected an identifier for a function definition");
    consumeToken();

    // parse arguments list prototype
    acceptOrErrorWithTokenInfo(Token::Type::paren_left, "Expected a left parenthesis");
    consumeToken();

    bool atLeastOne = false;
    while(!accept({Token::Type::paren_right})){
        std::string type, name;

        if(atLeastOne && accept(Token::Type::operator_comma))
            consumeToken();

        type = getIdentifierNameOrErrorWithTokenInfo("Expected a type specifier for functions's argument or right parenthesis");
        consumeToken();

        name = getIdentifierNameOrErrorWithTokenInfo("Expected an identifier for function's argument name");
        consumeToken();

        atLeastOne = true;

        if(!type.empty() && !name.empty()){
            functionDefinition->arguments.push_back(std::make_pair(type, name));
            //log({"Parsed argument's prototype: " + type + " " + name});
        }
    }
    consumeToken();

    // get function's body
    functionDefinition->body = parseBlockStatement();

    return functionDefinition;
}

BlockStatement::ptr Parser::parseBlockStatement() {
    debug("Parsing block");
    auto block = std::make_shared<BlockStatement>();

    acceptOrErrorWithTokenInfo(Token::Type::bracket_left, "Expected a left bracket");
    consumeToken();

    while(!accept(Token::Type::bracket_right)){
        auto statement = parseStatement();
        if(statement != nullptr)
            block->add(statement);
    }
    consumeToken();

    return block;
}

Statement::ptr Parser::parseStatement() {
    debug("Parsing statement");
    Statement::ptr statement = nullptr;

    if(accept(Token::Type::identifier)){

    }
    else if(accept(Token::Type::keyword_while)){

    }
    else if(accept(Token::Type::keyword_if)){

    }
    else if(accept(Token::Type::keyword_return)){
        consumeToken(); // consume return

        if(accept(Token::Type::operator_semicolon)){
            consumeToken();
            return std::make_shared<ReturnStatement>();
        }

        auto returnedValue = parseAssignable();
        acceptOrErrorWithTokenInfo(Token::Type::operator_semicolon, "Expected a semicolon");
        consumeToken();

        return std::make_shared<ReturnStatement>(returnedValue);
    }

    //consumeToken();
    // todo!!!
    //std::cout << "todo: parseStatement"; while(true);

    return statement;
}

Assignable::ptr Parser::buildBinaryExpression(Assignable::ptr left, Token::Type oper, Assignable::ptr right) {
    auto expression = std::make_shared<Expression>();
    expression->addOperand(left);
    expression->addOperator(oper);
    expression->addOperand(right);
    return expression;
}

Assignable::ptr Parser::buildUnaryExpression(Token::Type oper, Assignable::ptr operand) {
    auto expression = std::make_shared<Expression>();
    expression->addOperator(oper);
    expression->addOperand(operand);
    return expression;
}

Assignable::ptr Parser::parseAssignable() {
    debug("Parsing assignable");
    auto simpleExpression = parseSimpleExpression();

    if(accept({Token::Type::operator_equal,
              Token::Type::operator_not_equal,
              Token::Type::operator_greater,
              Token::Type::operator_less,
              Token::Type::operator_greater_equal,
              Token::Type::operator_less_equal})){
        auto relationalOperator = getAndConsumeToken().type;

        auto secondSimpleExpression = parseSimpleExpression();

        return buildBinaryExpression(simpleExpression, relationalOperator, secondSimpleExpression);
    }
    return simpleExpression;
}

Assignable::ptr Parser::parseSimpleExpression() {
    debug("Parsing simple expression");
    auto orExpression = parseOrExpression();
    if(accept({Token::Type::operator_plus,
               Token::Type::operator_minus,
               Token::Type::operator_or})){
        auto orOperator = getAndConsumeToken().type;

        auto secondOrExpression = parseOrExpression();

        return buildBinaryExpression(orExpression, orOperator, secondOrExpression);
    }
    return orExpression;
}

Assignable::ptr Parser::parseOrExpression() {
    debug("Parsing or expression");
    auto andExpression = parseAndExpression();
    if(accept({Token::Type::operator_multiply,
               Token::Type::operator_divide,
               Token::Type::operator_and,
               Token::Type::operator_concat})){
        auto andOperator = getAndConsumeToken().type;

        auto secondAndExpression = parseAndExpression();

        return buildBinaryExpression(andExpression, andOperator, secondAndExpression);
    }
    return andExpression;
}

Assignable::ptr Parser::parseAndExpression() {
    debug("Parsing and expression");
    if(accept(Token::Type::operator_not)){
        consumeToken();
        auto expression = parseAndExpression();
        return buildUnaryExpression(Token::Type::operator_not, expression);
    }
    else if(accept({Token::Type::const_int,
                    Token::Type::const_float,
                    Token::Type::const_string,
                    Token::Type::keyword_true,
                    Token::Type::keyword_false})){
        return std::make_shared<Literal>(getAndConsumeToken());
    }
    else if(accept(Token::Type::paren_left)){
        consumeToken();

        auto expression = parseAssignable();

        acceptOrErrorWithTokenInfo(Token::Type::paren_right, "Expected a closing parenthesis");
        consumeToken();

        return expression;
    }
    else if(accept(Token::Type::identifier)){
        return parseIdentifierFunctionCallOrMethodCall();
    }

    errorWithTokenInfo("Unexpected token " + getToken().representation);
    consumeToken();

    return nullptr;
}

Assignable::ptr Parser::parseIdentifierFunctionCallOrMethodCall() {
    debug("Parsing identifier, function call or method call");
    std::string name = std::get<std::string>(getAndConsumeToken().value);

    if(accept(Token::Type::operator_dot)){
        consumeToken();
        std::string methodName = getIdentifierNameOrErrorWithTokenInfo("Expected and identifier with method name");
        auto argumentsList = parseCallArguments();
        auto methodCall = std::make_shared<MethodCall>(name, methodName);

        methodCall->arguments = std::move(argumentsList);

        return methodCall;
    }
    else if(accept(Token::Type::paren_left)){
        auto functionCall = std::make_shared<FunctionCall>(name);

        auto argumentsList = parseCallArguments();
        functionCall->arguments = std::move(argumentsList);

        return functionCall;
    }

    errorWithTokenInfo("Expected operator dot or list of function call arguments");
    return nullptr;
}

FunctionCall::ArgumentsList Parser::parseCallArguments() {
    debug("Parsing call arguments");
    consumeToken(); // consume (

    FunctionCall::ArgumentsList argumentsList;

    bool atLeastOne = false;
    while(!accept({Token::Type::paren_right})){
        std::string type, name;

        if(atLeastOne && accept(Token::Type::operator_comma)) // todo: a co jeśli nie było argumentu?
            consumeToken();

        auto argument = parseAssignable();
        argumentsList.push_back(argument);

        atLeastOne = true;
    }

    acceptOrErrorWithTokenInfo(Token::Type::paren_right, "Expected a right parenthesis");
    consumeToken(); // consume )

    return argumentsList;
}

void Parser::debug(std::string msg) {
    // std::cout << msg << std::endl;
}



