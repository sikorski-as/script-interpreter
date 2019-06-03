#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "structures/ast/AST.h"
#include "structures/ast/ASTNodePrinter.h"
#include "structures/Token.h"

#include "modules/StringSource.h"
#include "modules/Lexer.h"
#include "modules/Parser.h"
#include "modules/SemCheck.h"

using std::string;
using std::vector;
using std::ifstream;

int main(int argc, const char* argv[])
{
	auto fileToString = [](std::string filename) {
		std::ifstream test1(filename);
		std::stringstream buffer;
		buffer << test1.rdbuf();
		return buffer.str();
	};

	StringSource source(fileToString("tests/editable_simple.txt"));
	Lexer lexer(source);
	Parser parser(lexer);
    SemCheck semcheck;

	try {
	    auto program = parser.parse();
        auto log = parser.getLog();
        for(auto& entry: log){
            std::cout << entry.text;
            if(entry.tokenInfo){
                std::cout << "(line:" << entry.line << ", column:" << entry.column << ")";
            }
            std::cout << std::endl;
        }

        if(parser.success()){
            std::cout << "Parser successfully parsed program" << std::endl << std::endl;
            printASTNode(program);
        }
        else{
            std::cout << "Parser failed" << std::endl;
            return 1;
        }

        auto executable = semcheck.check(program);
        auto semcheck_log = semcheck.getLog();
        for(auto& entry: semcheck_log){
            std::cout << entry.text << std::endl;
        }
        if(semcheck.success()){
            std::cout << "Starting execution..." << std::endl;
            executable->run();
            std::cout << "Execution finished..." << std::endl;
        }
        else{
            std::cout << "Semcheck failed" << std::endl;
            return 1;
        }

	}
	catch (Lexer::UnexpectedEndOfFile& e) {
		std::cout << "Lexer error: " << e.what() << std::endl << "Stopped." << std::endl;
		return 1;
	}
	catch (Lexer::UnexpectedSymbol& e) {
		std::cout << "Lexer error: " << e.what() << std::endl << "Stopped." << std::endl;
		return 2;
	}

	return 0;
}
