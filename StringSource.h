#pragma once
#include "Source.h"

class StringSource : public Source {
	std::string data;
	int position; // position of the last symbol that has been read
	int lineNumber;
	int columnNumber;
public:
	StringSource(std::string initString);
	virtual char nextSymbol();
	virtual char lastSymbol();
	virtual int getLineNumber();
	virtual int getColumnNumber();
	virtual bool eof();
};

