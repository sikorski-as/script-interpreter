#pragma once
#include <string>
#include <variant>
#include <string>
#include <unordered_map>

class Token
{
public:
	enum class Type {
		eof, unknown, identifier,

		paren_left, paren_right, bracket_left, bracket_right, // (, ), {, }

		keyword_if, keyword_else, keyword_elif, keyword_while,
		keyword_return, keyword_true, keyword_false,

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


const std::unordered_map<Token::Type, std::string> TOKEN_REPRESENTATION = {
        {Token::Type::eof, "end of file"},
        {Token::Type::unknown, "unknown"},
        {Token::Type::identifier, "idenfifier"},

        {Token::Type::paren_left, "("},
        {Token::Type::paren_right, ")"},
        {Token::Type::bracket_left, "{"},
        {Token::Type::bracket_right, "}"},

        {Token::Type::keyword_if, "if"},
        {Token::Type::keyword_else, "else"},
        {Token::Type::keyword_elif, "elif"},
        {Token::Type::keyword_while, "while"},

        {Token::Type::keyword_return, "return"},
        {Token::Type::keyword_true, "true"},
        {Token::Type::keyword_false, "false"},
        {Token::Type::const_int, "int literal"},
        {Token::Type::const_float, "float literal"},
        {Token::Type::const_string, "string literal"},

        {Token::Type::operator_comma, ","},
        {Token::Type::operator_semicolon, ";"},
        {Token::Type::operator_assign, "="},
        {Token::Type::operator_dot, "."},
        {Token::Type::operator_plus, "+"},
        {Token::Type::operator_minus, "-"},
        {Token::Type::operator_multiply, "*"},
        {Token::Type::operator_divide, "/"},
        {Token::Type::operator_concat, "~"},

        {Token::Type::operator_not, "not"},
        {Token::Type::operator_and, "and"},
        {Token::Type::operator_or, "or"},

        {Token::Type::operator_equal, "=="},
        {Token::Type::operator_not_equal, "!="},
        {Token::Type::operator_greater, ">"},
        {Token::Type::operator_less, "<"},
        {Token::Type::operator_greater_equal, ">="},
        {Token::Type::operator_less_equal, "<="},
};