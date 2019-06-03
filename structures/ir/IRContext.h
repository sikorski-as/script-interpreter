#ifndef TKOM_INTERPRETER_IRCONTEXT_H
#define TKOM_INTERPRETER_IRCONTEXT_H

#include <string>
#include <unordered_map>
#include "IRObject.h"

class IRContext {
    IRContext* upperContext = nullptr;
    std::unordered_map<std::string, IRObject::ptr> scopeSymbols;
public:
    IRContext(IRContext* = nullptr);
    void addSymbol(std::string&, IRObject::ptr);
    IRObject::ptr getSymbol(std::string&);
};

#endif //TKOM_INTERPRETER_IRCONTEXT_H
