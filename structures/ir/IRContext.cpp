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
