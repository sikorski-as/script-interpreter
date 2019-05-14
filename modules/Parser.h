#ifndef TKOM_INTERPRETER_PARSER_H
#define TKOM_INTERPRETER_PARSER_H

#include <memory>
#include <initializer_list>
#include "Lexer.h"
#include "../structures/ast/AST.h"
#include "../structures/Token.h"

class Parser {
public:
    struct LogEntry{
        std::string text = "";
        int line = 0, column = 0;
        bool tokenInfo = false;
    };

    class ParserException : public std::exception {
        std::string reason;
    public:
        ParserException() : reason("Syntax analysis error") {}
        ParserException(std::string reason) : reason(reason) {}
        virtual const char * what() = 0;
    };

    class UnexpectedEndOfFile : public ParserException {
        std::string reason;
    public:
        UnexpectedEndOfFile() : reason("Unexpected end of file during syntax analysis") {}
        UnexpectedEndOfFile(std::string reason) : reason(reason) {}
        const char * what() override {
            return reason.c_str();
        }
    };

    explicit Parser(Lexer&);
    Program::ptr parse();
    bool success();
    std::vector<LogEntry> getLog();
private:
    Lexer& lexer;
    std::vector<LogEntry> parserLog;
    bool successAchieved;

    Token consumeToken(); // consumes current and returns new token from the lexer
    Token getToken(); // returns current token from the lexer
    Token getAndConsumeToken(); // returns current token from the lexer, gets new before returning

    void log(LogEntry);
    void error(LogEntry);
    void debug(std::string);

    void errorWithTokenInfo(std::string);

    bool accept(Token::Type);
    bool accept(const std::initializer_list<Token::Type>&);

    bool acceptOrErrorWithTokenInfo(Token::Type, std::string errorMessage);
    bool acceptOrErrorWithTokenInfo(const std::initializer_list<Token::Type>&, std::string);
    std::string getIdentifierNameOrErrorWithTokenInfo(std::string message);

    FunctionDefinition::ptr parseFunctionDefinition();
    BlockStatement::ptr parseBlockStatement();
    Statement::ptr parseStatement();

    Assignable::ptr buildUnaryExpression(Token::Type, Assignable::ptr);
    Assignable::ptr buildBinaryExpression(Assignable::ptr, Token::Type, Assignable::ptr);

    Assignable::ptr parseAssignable();
    Assignable::ptr parseSimpleExpression();
    Assignable::ptr parseOrExpression();
    Assignable::ptr parseAndExpression();
    Assignable::ptr parseIdentifierPrefixForAssignable();

    Statement::ptr parseIdentifierPrefixForStatement();

    FunctionCall::ArgumentsList parseCallArguments();

};


#endif //TKOM_INTERPRETER_PARSER_H
