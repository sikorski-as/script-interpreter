#include "StdLib.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

unordered_map<string, vector<std::string>> StdLib::STDLIB_FUNCTIONS = {
        {"print", {"void", "print", "string"}},
        {"print_int", {"void", "print_int", "int"}},
        {"time", {"int", "time"}},
        {"random", {"int", "random"}},
        {"Network", {"Network", "Network", "string"}},
        {"Algorithm", {"Algorithm", "Algorithm", "string"}},
        {"Evaluator", {"Evaluator", "Evaluator", "string"}}
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

IRObject::ptr StdLib::libraryFunctionCall(std::string &fname, std::vector<IRObject::ptr> args) {
    if(fname == "print"){
        std::cout << std::get<std::string>(args[0]->value) << std::endl;
        return nullptr;
    }
    else if(fname == "print_int"){
        std::cout << std::get<int>(args[0]->value) << std::endl;
        return nullptr;
    }
    else if(fname == "Network"){
        std::cout << "<calling Network(string) library function>" << std::endl;
        auto object = std::make_shared<IRObject>();
        object->type = "Network";
        return object;
    }
    else if(fname == "Algorithm"){
        std::cout << "<calling Algorithm(string) library function>" << std::endl;
        auto object = std::make_shared<IRObject>();
        object->type = "Algorithm";
        return object;
    }
    else if(fname == "Evaluator"){
        std::cout << "<calling Evaluator(string) library function>" << std::endl;
        auto object = std::make_shared<IRObject>();
        object->type = "Evaluator";
        return object;
    }
    else if(fname == "random"){
        auto object = std::make_shared<IRObject>();
        srand(time(NULL));
        object->value = static_cast<int>(rand());
        object->type = "int";
        return object;
    }
    else if(fname == "time"){
        auto object = std::make_shared<IRObject>();
        object->value = static_cast<int>(time(NULL));
        object->type = "int";
        return object;
    }

    return nullptr;
}
