#include "settings.h"
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

auto fileToString = [](std::string filename) {
    std::ifstream test1(filename);
    std::stringstream buffer;
    buffer << test1.rdbuf();
    return buffer.str();
};

int main(int argc, const char* argv[])
{
    std::vector<std::string> arguments(argv + 1, argv + argc);

    if(arguments.size() == 0){
        std::cout << "Interpreter requires at least 1 argument, "
                     "--help to show available options" << std::endl;
        return 1;
    }
    else if(arguments[0] == "--help"){
        std::cout << "Available commands:" << std::endl
                << "--help\t\t\t\tshow this message\n"
                << "--debug_execute\t\texecute script and print syntax tree\n"
                << "--execute <filename>\t\texecute given script\n";
        return 0;
    }

    std::string data;
    bool debug = false;
    if(arguments[0] == "--debug_execute"){
        if(arguments.size() >= 2){
            data = fileToString(arguments[1]);
            if(data == ""){
                std::cout << "File not found" << std::endl;
                return 2;
            }
            debug = true;
        }
        else {
            std::cout << "--debug_execute option requires the filepath only" << std::endl;
            return 3;
        }
    }
    else if(arguments[0] == "--execute"){
        if(arguments.size() >= 2){
            data = fileToString(arguments[1]);
            if(data == ""){
                std::cout << "File not found" << std::endl;
                return 4;
            }
        }
        else {
            std::cout << "--execute option requires the filepath only" << std::endl;
            return 5;
        }
    }
    else{
        std::cout << "Unknown option, "
                     "--help to show available options" << std::endl;
        return 6;
    }

	StringSource source(data);
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
            if(debug){
                printASTNode(program);
                std::cout << std::endl;
            }
        }
        else{
            std::cout << "Parser failed" << std::endl;
            return 7;
        }

        auto executable = semcheck.check(program);
        auto semcheck_log = semcheck.getLog();
        for(auto& entry: semcheck_log){
            std::cout << entry.text << std::endl;
        }
        if(semcheck.success()){
            std::cout << "Starting execution..." << std::endl << std::endl;
            executable->run();
            std::cout << "Execution finished..." << std::endl << std::endl;
        }
        else{
            std::cout << "Semcheck failed" << std::endl;
            return 8;
        }

	}
	catch (Lexer::UnexpectedEndOfFile& e) {
		std::cout << "Lexer error: " << e.what() << std::endl << "Stopped." << std::endl;
		return 9;
	}
	catch (Lexer::UnexpectedSymbol& e) {
		std::cout << "Lexer error: " << e.what() << std::endl << "Stopped." << std::endl;
		return 10;
	}

	return 0;
}
