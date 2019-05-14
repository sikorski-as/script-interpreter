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

	//StringSource source("   int x = 0; void f_o_O(){}\nstring s = \"hello, there!_   \" {aa;\nf();\n evaluator ev_01();    .\"  ,\"");
	//StringSource source(fileToString("tests/test_valid.txt"));
	//StringSource source(fileToString("tests/test_empty.txt"));
	//StringSource source(fileToString("tests/test_unexpected_eof_float.txt"));
	//StringSource source(fileToString("tests/test_unexpected_eof_string.txt"));
	//StringSource source(fileToString("tests/test_expected_digit_float.txt"));
	/*StringSource source("int main(){"
                     "if(foo.boo((1.0+5+3)*5/3, -true, lol))"
                     "{while(i<5){return -15 ~ \"haha\";}"
                     ""
                     "}"
                     "}");*/
	//StringSource source("void foo(int x, float f){if(true){} return (0+1) * 3;}int main(int argc){}int boo(){}");

	StringSource source(fileToString("tests/editable.txt"));
	Lexer lexer(source);
	Parser parser(lexer);

	try {
        /*int i = 0;
		while (true) {
			Token t = lexer.getToken();
			lexer.consumeToken();

			if (t.line != i) {
				i = t.line;
				std::cout << std::endl;
			}
			std::cout << std::string(t) << std::endl;
			if (t.type == Token::Type::eof)
				break;
		}*/

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
