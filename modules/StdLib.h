#ifndef TKOM_INTERPRETER_STDLIB_H
#define TKOM_INTERPRETER_STDLIB_H

#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <variant>
#include "../structures/ir/IRObject.h"
using namespace std;

class StdLib {
public:
    static bool hasFunction(std::string&);
    //static std::unordered_map<std::string, bool> STDLIB_FUNCTIONS;
    static std::unordered_map<string, vector<std::string>> STDLIB_FUNCTIONS;

    static bool hasType(std::string&);
    static std::unordered_map<std::string, bool> STDLIB_TYPES;

    static bool hasMethod(std::string&, std::string&);
    static std::unordered_map<string, unordered_map<string, vector<std::string>>> STDLIB_METHODS;

    static IRObject::ptr libraryFunctionCall(std::string&, std::vector<IRObject::ptr>);
};

#endif //TKOM_INTERPRETER_STDLIB_H
