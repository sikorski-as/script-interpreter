#include "StdLib.h"

unordered_map<string, vector<std::string>> StdLib::STDLIB_FUNCTIONS = {
        {"print", {"void", "print", "string"}},
        {"time", {"int", "time"}},
        {"random", {"int", "random"}},
        {"Network", {"Network", "Network"}},
        {"Algorithm", {"Algorithm", "Algorithm"}},
        {"Evaluator", {"Evaluator", "Evaluator"}}
};

bool StdLib::hasFunction(std::string & fname) {
    return StdLib::STDLIB_FUNCTIONS.count(fname) > 0;
}

std::unordered_map<std::string, bool> StdLib::STDLIB_TYPES = {
        {"void", true},
        {"int", true},
        {"float", true},
        {"string", true},
        {"bool", true},
        {"Network", true},
        {"Algorithm", true},
        {"Evaluator", true},
};

bool StdLib::hasType(std::string& tname) {
    return StdLib::STDLIB_TYPES.count(tname) > 0;
}

bool StdLib::hasMethod(std::string &, std::string &) {
    return false;
}

using namespace std;
std::unordered_map<string, unordered_map<string, vector<std::string>>> StdLib::STDLIB_METHODS = {
        {
            "Network",
            {
                {"load", {"void", "load", "string"}},
                {"save", {"void", "save", "string"}},
                {"run", {"void", "run", "Algorithm"}},
                {"eval", {"float", "eval", "Evaluator"},}
            }
        },
        {
            "Algorithm",
            {
                {"set", {"void", "set", "string", "float"}},
                {"get", {"float", "get", "string"}}
            }
        },
        {
            "Evaluator",
            {
                {"set", {"void", "set", "string", "float"}},
                {"get", {"float", "get", "string"}}
            }
        }
};