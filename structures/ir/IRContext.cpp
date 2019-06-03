#include "IRContext.h"

IRContext::IRContext(IRContext *upper) {
    upperContext = upper;
}

void IRContext::addSymbol(std::string& name, IRObject::ptr value) {
    scopeSymbols[name] = value;
    // scopeSymbols[name] = std::make_shared<IRObject>(*value);
}

IRObject::ptr IRContext::getSymbol(std::string& name) {
    if(scopeSymbols.count(name) > 0){
        return scopeSymbols[name];
    }
    if(upperContext){
        return upperContext->getSymbol(name);
    }
    return nullptr;
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

void IRContext::setSymbol(std::string & name, IRObject::ptr value) {
    if(scopeSymbols.count(name) > 0){
        scopeSymbols[name] = value;
    }
    if(upperContext){
        return upperContext->setSymbol(name, value);
    }
}
