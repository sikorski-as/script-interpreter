#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "StringSource.h"
#include "Lexer.h"
#include "ast/ASTNode.h"
#include "ast/Program.h"
#include "ast/ReturnStatement.h"
#include "ast/FunctionCall.h"
#include "ast/Literal.h"

using std::string;
using std::vector;
using std::ifstream;

int main(int argc, const char* argv[])
{
    Program program;

    auto mainBody = std::make_shared<BlockStatement>();
    mainBody->add(
            std::make_shared<ReturnStatement>()
    );

    program.add(
            std::make_shared<FunctionDefinition>(
                    std::string("void"),
                    std::string("main"),
                    FunctionDefinition::ArgumentsListPrototype(),
                    mainBody
            )
    );

    Assignable::ptr rvalue = std::make_shared<Literal>(Token());
    if(rvalue->getType() == ASTNode::Type::literal){
        auto lit = std::dynamic_pointer_cast<Literal>(rvalue);
        std::cout << lit;
    }


    /*
    vector<string> args(argv + 1, argv + argc);
    if(args.size() == 0)
    {
        //std::cout << "Source file not specified. Closing.";
        //return 1;
    }
    */

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
	StringSource source("int main(){\n\treturn 0;\n}");

	Lexer lexer(source);

	int i = 0;
	try {
		while (true) {
			Token t = lexer.getToken();
			if (t.line != i) {
				i = t.line;
				std::cout << std::endl;
			}
			std::cout << std::string(t) << std::endl;
			if (t.type == Token::Type::eof)
				break;
		}
	}
	catch (Lexer::UnexpectedEndOfFile e) {
		std::cout << "Lexer error: " << e.what() << std::endl << "Stopped." << std::endl;
		return 1;
	}
	catch (Lexer::UnexpectedSymbol e) {
		std::cout << "Lexer error: " << e.what() << std::endl << "Stopped." << std::endl;
		return 2;
	}

	return 0;
}
