#pragma once
#include <string>
#include <variant>
#include <string>

class Token
{
public:
	enum class Type {
		eof,
		unknown,
		identifier,

		paren_left,    // (
		paren_right,   // )

		bracket_left,  // {
		bracket_right, // }

		keyword_if,
		keyword_else,
		keyword_elif,
		keyword_while,
		keyword_return,
		keyword_true,
		keyword_false,

		/*
		keyword_void, 
		keyword_bool,
		keyword_int,
		keyword_float,
		keyword_string,
		keyword_network,
		keyword_algorithm,
		keyword_evaluator,
		*/

		const_int, // -?[1-9][0-9]*
		const_float, // -?[1-9][0-9]*.[0-9]*
		const_string, // "[^\"]*"

		operator_comma, // ,
		operator_semicolon, // ;
		operator_assign, // =
		operator_dot, // .
		operator_plus,
		operator_minus,
		operator_multiply,
		operator_divide,
		operator_concat, // ~

		operator_not, // !
		operator_and, // &
		operator_or, // |

		operator_equal, // ==
		operator_not_equal, // !=
		operator_greater, // >
		operator_less, // <
		operator_greater_equal, // >=
		operator_less_equal // <=
	} type;
	int line;
	int column;
	std::variant<bool, int, float, std::string> value;
	std::string representation;

	operator std::string();
	Token(Type type = Token::Type::unknown, std::string="token unkown");
	~Token() = default;
};
