#ifndef TKOM_INTERPRETER_IROBJECT_H
#define TKOM_INTERPRETER_IROBJECT_H

#include <variant>
#include <memory>
#include <string>
#include "../../stdlib/includes.h"

class IRObject {
public:
    typedef std::shared_ptr<IRObject> ptr;
    class AccessException{};

    Network net;
    Algorithm alg;
    Evaluator eval;
    std::variant<bool, int, float, std::string> value;

    std::string type;
};


#endif //TKOM_INTERPRETER_IROBJECT_H
