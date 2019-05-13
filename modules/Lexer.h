#pragma once
#include "Source.h"
#include "../structures/Token.h"
#include <string>
#include <map>

class Lexer
{
	Source& source;
	char symbol;

	void skipWhitespace();
	void skipComment();
	void nextSymbol();
	void nextSymbolSafe();

	Token findKeywordOrIdentifier();
	Token findNumber();

	Token checkIfAssignmentOrEqual();
	Token checkIfNotOrNotEqual();
	Token findStringConstant();

	Token checkIfLessOrLessEqual();
	Token checkIfGreaterOrGreaterEqual();

	bool hasBufferedToken;
	Token bufferedToken;
	Token buildToken();

	std::string getSourcePointer();
public:
	Lexer(Source&);
	~Lexer() = default;

	void consumeToken();
	Token getToken();

	class LexerException : public std::exception {
		std::string reason;
	public:
	    int line = 0, column = 0;
		LexerException() : reason("Lexical analysis error") {}
		LexerException(std::string reason) : reason(reason) {}
		virtual const char * what() = 0;
	};

	class UnexpectedEndOfFile : public LexerException {
		std::string reason;
	public:
		UnexpectedEndOfFile() : reason("Unexpected end of file during lexical analysis") {}
		UnexpectedEndOfFile(std::string reason) : reason(reason) {}
		const char * what() override {
			return reason.c_str();
		}
	};

	class UnexpectedSymbol : public LexerException {
		std::string reason;
	public:
		UnexpectedSymbol() : reason("Unexpected symbol during lexical analysis") {}
		UnexpectedSymbol(std::string reason) : reason(reason) {}
		const char * what() override {
			return reason.c_str();
		}
	};
};

const std::map<std::string, Token::Type> KEYWORDS_MAP = {
	{"if", Token::Type::keyword_if},
	{"else", Token::Type::keyword_else},
	{"elif", Token::Type::keyword_elif},
	{"while", Token::Type::keyword_while},
	{"return", Token::Type::keyword_return},
	{"true", Token::Type::keyword_true},
	{"false", Token::Type::keyword_false},

	// these can be deleted
	/*
	{"void", Token::Type::keyword_void},
	{"bool", Token::Type::keyword_bool},
	{"int", Token::Type::keyword_int},
	{"float", Token::Type::keyword_float},
	{"string", Token::Type::keyword_string},
	{"network", Token::Type::keyword_network},
	{"algorithm", Token::Type::keyword_algorithm},
	{"evaluator", Token::Type::keyword_evaluator}
	*/
};

