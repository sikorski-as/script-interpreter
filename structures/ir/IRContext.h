#ifndef TKOM_INTERPRETER_IRCONTEXT_H
#define TKOM_INTERPRETER_IRCONTEXT_H

#include <memory>
#include <string>
#include <unordered_map>
//#include "IRFunction.h" // circular dependency
#include "IRObject.h"

class IRFunction;
class IRContext {
public:
    IRContext* upperContext = nullptr;
    std::unordered_map<std::string, IRObject::ptr> scopeSymbols;
    std::unordered_map<std::string, std::shared_ptr<IRFunction>> definedFunctions;

    IRContext(IRContext* = nullptr);
    void addSymbol(std::string&, IRObject::ptr);
    IRObject::ptr getSymbol(std::string&);
    void setSymbol(std::string&, IRObject::ptr);

    std::shared_ptr<IRFunction> getFunction(std::string&);
};

#endif //TKOM_INTERPRETER_IRCONTEXT_H
