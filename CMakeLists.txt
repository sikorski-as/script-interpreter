cmake_minimum_required(VERSION 3.13)
project(tkom_interpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(tkom_interpreter
        main.cpp

        modules/Source.cpp modules/Source.h
        modules/StringSource.cpp modules/StringSource.h

        modules/Lexer.cpp modules/Lexer.h
        structures/Token.cpp structures/Token.h

        structures/ast/ASTNode.h
        structures/ast/Program.h

        structures/ast/FunctionDefinition.h
        structures/ast/Statement.h
        structures/ast/BlockStatement.h
        structures/ast/IfStatement.h
        structures/ast/Assignable.h
        structures/ast/WhileStatement.h
        structures/ast/ReturnStatement.h
        structures/ast/VariableDeclaration.h
        structures/ast/VariableDefinition.h
        structures/ast/VariableAssignment.h structures/ast/Expression.h structures/ast/Literal.h structures/ast/Variable.h structures/ast/FunctionCall.h structures/ast/MethodCall.h)

