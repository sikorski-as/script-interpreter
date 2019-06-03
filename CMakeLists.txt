cmake_minimum_required(VERSION 3.13)
project(tkom_interpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(tkom_interpreter
        main.cpp

        modules/Source.cpp modules/Source.h
        modules/StringSource.cpp modules/StringSource.h
        modules/Lexer.cpp modules/Lexer.h
        modules/Parser.cpp modules/Parser.h

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
        structures/ast/VariableAssignment.h
        structures/ast/Expression.h
        structures/ast/Literal.h
        structures/ast/Variable.h
        structures/ast/FunctionCall.h
        structures/ast/MethodCall.h structures/ast/AST.h structures/ast/ASTNodePrinter.h modules/SemCheck.cpp modules/SemCheck.h structures/ir/IRFunction.h structures/ir/IR.h structures/ir/IRProgram.cpp structures/ir/IRProgram.h structures/ir/IRContext.cpp structures/ir/IRContext.h modules/StdLib.cpp modules/StdLib.h structures/ir/ContextPrototype.cpp structures/ir/ContextPrototype.h structures/ir/IRExecutable.h structures/ir/IRObject.cpp structures/ir/IRObject.h structures/ir/IRStatement.h structures/ir/IRBlock.h structures/ir/IRAssignable.h structures/ir/IRIfStatement.h structures/ir/IRWhileStatement.h structures/ir/IRVarDeclaration.h structures/ir/IRVarDefinition.h structures/ir/IRVarAssignment.h structures/ir/IRReturnStatement.h structures/ir/IRFunctionCall.h structures/ir/IRLiteral.h structures/ir/IRVariable.h structures/ir/IRExpression.h stdlib/Network.cpp stdlib/Network.h stdlib/Algorithm.cpp stdlib/Algorithm.h stdlib/Evaluator.cpp stdlib/Evaluator.h stdlib/includes.h)

