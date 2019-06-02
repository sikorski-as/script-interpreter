#ifndef TKOM_INTERPRETER_STDLIB_H
#define TKOM_INTERPRETER_STDLIB_H

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class StdLib {
public:
    static bool hasFunction(std::string&);
    static std::unordered_map<std::string, bool> STDLIB_FUNCTIONS;

    static bool hasType(std::string&);
    static std::unordered_map<std::string, bool> STDLIB_TYPES;

    static bool hasMethod(std::string&, std::string&);
    static std::unordered_map<string, unordered_map<string, vector<std::string>>> STDLIB_METHODS;
};

#endif //TKOM_INTERPRETER_STDLIB_H
