#include "StringSource.h"

StringSource::StringSource(std::string initString) : data(initString) {
	position = -1;
	lineNumber = 0;
	columnNumber = -1;
}

char StringSource::nextSymbol() {
	if (eof()) {
		throw Source::EndOfFileException();
	}

	position++;

	if (position > 0 && data[position - 1] == '\n'){
		columnNumber = 0;
		lineNumber++;
	}
	else
		columnNumber++;

	return data[position];
}

char StringSource::lastSymbol() {
	if (position == -1) {
		throw Source::NoLastSymbolException();
	}
	return data[position];
}

int StringSource::getLineNumber() {
	return lineNumber;
}

int StringSource::getColumnNumber() {
	return columnNumber;
}

bool StringSource::eof() {
	return position == data.size();
}

