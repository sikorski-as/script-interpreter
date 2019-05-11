#pragma once
#include <memory>
class ASTNode
{
public:
	typedef std::shared_ptr<ASTNode> ptr;
	enum class Type {
		program,
		
		// statements
		block_statement,
		if_statement,
		while_statement,

		var_declaration,
		var_definition,
		var_assignment,

		return_statement,

		function_definition,

		expression,
		literal,
		variable,
		function_call,
		method_call
	};

	ASTNode() = default;
	virtual ~ASTNode() = default;

	virtual Type getType() const = 0;
};

