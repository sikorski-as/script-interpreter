#include "Lexer.h"
#include <iostream>
#include <cctype>

void Lexer::skipWhitespace()
{
	while (isspace(symbol))
		nextSymbolSafe();

	//std::cout << "skipWhitespace()" << std::endl;
}

void Lexer::skipComment() {
	if (symbol != '#')
		return;

	while (!source.eof()) {
		if (symbol == '\n') {
			nextSymbolSafe();
			if (symbol == '#') {
				continue;
			}
			else
				break;
		}
		nextSymbolSafe();
	}
}

void Lexer::nextSymbol()
{
	symbol = source.nextSymbol();
}

void Lexer::nextSymbolSafe()
{
	if (!source.eof())
		symbol = source.nextSymbol();
}

Token Lexer::findKeywordOrIdentifier()
{
	std::string word;

	Token t;
	t.column = source.getColumnNumber();
	t.line = source.getLineNumber();

	do {
		word += symbol;
		nextSymbolSafe();
	} while (!source.eof() && (isdigit(symbol) || isalpha(symbol) || symbol == '_'));
	

	if (KEYWORDS_MAP.count(word) > 0) {
		t.type = KEYWORDS_MAP.at(word);
		t.representation = "keyword \"" + word + "\"";
	}
	else {
		t.type = Token::Type::identifier;
		t.value = word;
		t.representation = "identifier \"" + word + "\"";
	}
	
	return t;
}

Token Lexer::findNumber()
{
	Token t;
	t.column = source.getColumnNumber();
	t.line = source.getLineNumber();

	int i = 0;
	float f = 0.0;
	bool integer = true;
	float fraction = 0.1f;

	while (!source.eof()) {
		if (isdigit(symbol)) {
			if (integer) {
				i = i * 10 + static_cast<int>(symbol) - 48;
			}
			else {
				f += fraction * (static_cast<float>(symbol) - 48);
				fraction /= 10;
			}
			nextSymbolSafe();
		}
		else if (symbol == '.') {
			if (integer) {
				integer = false;
				f = static_cast<float>(i);
				nextSymbolSafe();
				if (source.eof())
					throw Lexer::UnexpectedEndOfFile("Unexpected end of file when parsing a number" + getSourcePointer());
				else if(!isdigit(symbol))
					throw Lexer::UnexpectedSymbol("Expected a digit after .");
			}
			else {
				throw Lexer::UnexpectedSymbol("Unexpected . when parsing a number");
			}
		}
		else if (isalpha(symbol)) {
			throw Lexer::UnexpectedSymbol("Unexpected symbol when parsing a number");
		}
		else {
			break;
		}
	}

	if (integer) {
		t.type = Token::Type::const_int;
		t.value = i;
		t.representation = "int constant " + std::to_string(i);
	}
	else {
		t.type = Token::Type::const_float;
		t.value = f;
		t.representation = "float constant " + std::to_string(f);
	}
	
	return t;
}

Token Lexer::findStringConstant() {
	std::string word;

	Token t(Token::Type::const_string);
	t.column = source.getColumnNumber();
	t.line = source.getLineNumber();
	
	nextSymbolSafe();

	while (!source.eof() && symbol != '"') {
		word += symbol;
		nextSymbolSafe();
	}

	if(source.eof() && symbol != '"')
		throw Lexer::UnexpectedEndOfFile("Expected \" before end of file");
	else {
		t.value = word;
		t.representation = "string constant \"" + word + "\"";
		nextSymbolSafe();
	}
	
	return t;
}

Token Lexer::checkIfAssignmentOrEqual()
{
	Token t;
	t.column = source.getColumnNumber();
	t.line = source.getLineNumber();

	nextSymbolSafe();

	if (!source.eof() && symbol == '=') {
		t.type = Token::Type::operator_equal;
		t.representation = "operator ==";
		nextSymbolSafe();
	}
	else {
		t.type = Token::Type::operator_assign;
		t.representation = "operator =";
	}

	return t;
}

Token Lexer::checkIfNotOrNotEqual()
{
	Token t;
	t.column = source.getColumnNumber();
	t.line = source.getLineNumber();

	nextSymbolSafe();
	
	if (!source.eof() && symbol == '=') {
		t.type = Token::Type::operator_not_equal;
		t.representation = "operator !=";
		nextSymbolSafe();
	}
	else {
		t.type = Token::Type::operator_not;
		t.representation = "operator !";
	}

	return t;
}

Token Lexer::checkIfLessOrLessEqual()
{
	Token t;

	t.column = source.getColumnNumber();
	t.line = source.getLineNumber();

	nextSymbolSafe();

	if (!source.eof() && symbol == '=') {
		t.type = Token::Type::operator_less_equal;
		t.representation = "operator <=";
		nextSymbolSafe();
	}
	else {
		t.type = Token::Type::operator_less;
		t.representation = "operator <";
	}

	return t;
}

Token Lexer::checkIfGreaterOrGreaterEqual()
{
	Token t;
	t.column = source.getColumnNumber();
	t.line = source.getLineNumber();

	nextSymbolSafe();

	if (!source.eof() && symbol == '=') {
		t.type = Token::Type::operator_greater_equal;
		t.representation = "operator >=";
		nextSymbolSafe();
	}
	else {
		t.type = Token::Type::operator_greater;
		t.representation = "operator >";
	}

	return t;
}

Token Lexer::buildToken() {
    skipWhitespace();
    skipComment();

    if (!source.eof()) {
        if (isalpha(symbol))
            return findKeywordOrIdentifier(); // done
        else if (isdigit(symbol)) {
            return findNumber(); // todo
        }

        Token t(Token::Type::unknown, "unkown token");
        t.column = source.getColumnNumber();
        t.line = source.getLineNumber();

        switch (symbol) {
            case '"':
                return findStringConstant(); // done
            case '=':
                return checkIfAssignmentOrEqual(); // done
            case '!':
                return checkIfNotOrNotEqual(); // done
            case '<':
                return checkIfLessOrLessEqual(); // done
            case '>':
                return checkIfGreaterOrGreaterEqual(); // done
            case '-':
                nextSymbolSafe();
                t.type = Token::Type::operator_minus;
                t.representation = "operator -";
                return t;
            case '{':
                nextSymbolSafe();
                t.type = Token::Type::bracket_left;
                t.representation = "token {";
                return t;
            case '}':
                nextSymbolSafe();
                t.type = Token::Type::bracket_right;
                t.representation = "token }";
                return t;
            case '(':
                nextSymbolSafe();
                t.type = Token::Type::paren_left;
                t.representation = "token (";
                return t;
            case ')':
                nextSymbolSafe();
                t.type = Token::Type::paren_right;
                t.representation = "token )";
                return t;
            case '.':
                nextSymbolSafe();
                t.type = Token::Type::operator_dot;
                t.representation = "operator .";
                return t;
            case ',':
                nextSymbolSafe();
                t.type = Token::Type::operator_comma;
                t.representation = "operator ,";
                return t;
            case ';':
                nextSymbolSafe();
                t.type = Token::Type::operator_semicolon;
                t.representation = "token ;";
                return t;
            case '+':
                nextSymbolSafe();
                t.type = Token::Type::operator_plus;
                t.representation = "operator +";
                return t;
            case '*':
                nextSymbolSafe();
                t.type = Token::Type::operator_multiply;
                t.representation = "operator *";
                return t;
            case '/':
                nextSymbolSafe();
                t.type = Token::Type::operator_divide;
                t.representation = "operator /";
                return t;
            case '~':
                nextSymbolSafe();
                t.type = Token::Type::operator_concat;
                t.representation = "operator ~";
                return t;
            case '&':
                nextSymbolSafe();
                t.type = Token::Type::operator_and;
                t.representation = "operator &";
                return t;
            case '|':
                nextSymbolSafe();
                t.type = Token::Type::operator_or;
                t.representation = "operator |";
                return t;
        }
        //std::cout << "???: " << symbol << std::endl;
        nextSymbolSafe();
        return t;
    }
    else {
        Token t(Token::Type::eof, "token eof");
        t.column = source.getColumnNumber();
        t.line = source.getLineNumber();
        return t;
    }
}

//
// public
//

Lexer::Lexer(Source& source)
	:source(source), symbol(' '), hasBufferedToken(false)
{
	
}

Token Lexer::getToken()
{
    if(!hasBufferedToken){
        hasBufferedToken = true;
        bufferedToken = buildToken();
    }

    return bufferedToken;
}

void Lexer::consumeToken() {
    bufferedToken = buildToken();
}

std::string Lexer::getSourcePointer() {
    return "(line: " + std::to_string(source.getLineNumber()) + ", column: " + std::to_string(source.getColumnNumber()) + ")";
}
