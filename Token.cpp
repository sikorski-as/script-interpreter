#include "Token.h"
#include <sstream>


Token::operator std::string()
{
	std::stringstream s;
	s << line << ':' << column << ": " << representation;
	return s.str();
}

Token::Token(Type type, std::string repr)
	: type(type), line(-1), column(-1), representation(repr)
{

}
