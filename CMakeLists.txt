cmake_minimum_required(VERSION 3.13)
project(tkom_interpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(tkom_interpreter
        main.cpp

        Source.cpp Source.h
        StringSource.cpp StringSource.h

        Lexer.cpp Lexer.h
        Token.cpp Token.h

        ast/ASTNode.h
        ast/Program.h

        ast/FunctionDefinition.h
        ast/Statement.h
        ast/BlockStatement.h
        ast/IfStatement.h
        ast/Assignable.h
        ast/WhileStatement.h
        ast/ReturnStatement.h
        ast/VariableDeclaration.h
        ast/VariableDefinition.h
        ast/VariableAssignment.h ast/Expression.h ast/Literal.h ast/Variable.h ast/FunctionCall.h ast/MethodCall.h)

