#include "StdLib.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

unordered_map<string, vector<std::string>> StdLib::STDLIB_FUNCTIONS = {
        {"system", {"void", "system", "string"}},
        {"sleep", {"void", "sleep", "int"}},

        {"print", {"void", "print", "string"}},
        {"print_int", {"void", "print_int", "int"}},
        {"println", {"void", "println", "string"}},
        {"println_int", {"void", "println_int", "int"}},

        {"get_int", {"int", "get_int"}},
        {"get_string", {"string", "get_string"}},
        {"get_float", {"float", "get_float"}},

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
    if(fname == "system"){
        auto command = std::get<std::string>(args[0]->value);
        system(command.c_str());
        return nullptr;
    }
    else if(fname == "sleep"){
        auto seconds = std::get<int>(args[0]->value);
        sleep(seconds);
        return nullptr;
    }
    else if(fname == "print"){
        std::cout << std::get<std::string>(args[0]->value);
        return nullptr;
    }
    else if(fname == "println"){
        std::cout << std::get<std::string>(args[0]->value) << std::endl;
        return nullptr;
    }
    else if(fname == "print_int"){
        std::cout << std::get<int>(args[0]->value);
        return nullptr;
    }
    else if(fname == "println_int"){
        std::cout << std::get<int>(args[0]->value) << std::endl;
        return nullptr;
    }
    else if(fname == "get_int"){
        std::cout << "enter int value: "<< std::flush;

        int value;
        std::cin >> value;
        auto object = std::make_shared<IRObject>();
        object->type = "int";
        object->value = value;

        return object;
    }
    else if(fname == "get_string"){
        std::cout << "enter string value: " << std::flush;

        std::string value;
        std::cin >> value;

        auto object = std::make_shared<IRObject>();
        object->type = "string";
        object->value = value;

        return object;
    }
    else if(fname == "get_float"){
        std::cout << "enter float value: "<< std::flush;

        float value;
        std::cin >> value;
        auto object = std::make_shared<IRObject>();
        object->type = "float";
        object->value = value;

        return object;
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
