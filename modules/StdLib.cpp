
#include "StdLib.h"

std::unordered_map<std::string, bool> StdLib::STDLIB_FUNCTIONS = {
        {"print", true},
        {"time", true},
        {"Network", true},
        {"Algorithm", true},
        {"Evaluator", true},
        {"random", true},
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