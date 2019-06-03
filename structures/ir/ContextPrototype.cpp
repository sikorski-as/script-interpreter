#include "ContextPrototype.h"

void ContextPrototype::addVariable(ContextPrototype::VariablePrototype& varproto) {
    scopeVariables[varproto.second] = varproto;
    functionArgsOrder.push_back(varproto);
}


bool ContextPrototype::isVariableInScope(std::string& varname) {
    if(scopeVariables.count(varname) > 0)
        return true;
    else{
        if(upperContext != nullptr){
            return upperContext->isVariableInScope(varname);
        }
    }
    return false;
}

std::string ContextPrototype::getVariableType(std::string& varname) {
    if(scopeVariables.count(varname) > 0)
        return scopeVariables[varname].first;
    else{
        if(upperContext != nullptr){
            return upperContext->getVariableType(varname);
        }
    }

    throw VariableNotFound();
}

bool ContextPrototype::hasReturnStatement() {
    return hasReturn;
}

void ContextPrototype::returnStatementSpotted() {
    hasReturn = true;
    if(upperContext != nullptr){
        upperContext->returnStatementSpotted();
    }
}

IRContext *ContextPrototype::createInstance(std::vector<IRObject::ptr> values) {
    auto context = new IRContext();
    for(int i = 0; i < values.size(); i++){
        context->addSymbol(functionArgsOrder[i].second, values[i]);
    }
    return context;
}
