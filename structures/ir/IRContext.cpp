#include "IRContext.h"

IRContext::IRContext(IRContext *upper) {
    upperContext = upper;
}

void IRContext::addSymbol(std::string& name, IRObject::ptr value) {
    scopeSymbols[name] = value;
}

IRObject::ptr IRContext::getSymbol(std::string& name) {
    return scopeSymbols[name];
}

std::shared_ptr<IRFunction> IRContext::getFunction(std::string& name) {
    if(definedFunctions.count(name) > 0){
        return definedFunctions[name];
    }
    if(upperContext){
        return upperContext->getFunction(name);
    }
    return nullptr;
}
