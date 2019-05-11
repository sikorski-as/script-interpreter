#pragma once
#include <string>
#include <exception>
class Source
{
public:
	
	virtual char nextSymbol() = 0;
	virtual char lastSymbol() = 0;
	virtual int getLineNumber() = 0;
	virtual int getColumnNumber() = 0;
	virtual bool eof() = 0; // last char of source has been read

	class EndOfFileException : public std::exception {
	public:
		virtual const char * what() {
			return "end of file reached";
		}
	};
	class NoLastSymbolException : public std::exception {
	public:
		virtual const char * what() {
			return "there is no last symbol for this source";
		}
	};
};

