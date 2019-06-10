#ifndef TKOM_INTERPRETER_CONTEXTPROTOTYPE_H
#define TKOM_INTERPRETER_CONTEXTPROTOTYPE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
// #include "IRFunction.h"
#include "IRContext.h" // circular dependency
#include "IRObject.h"

class ContextPrototype {
public:
    typedef std::pair<std::string, std::string> VariablePrototype;
    class VariableNotFound{};

    explicit ContextPrototype(ContextPrototype* upperContext = nullptr) : upperContext(upperContext), hasReturn(false){}

    void addVariable(VariablePrototype&);
    bool isVariableInScope(std::string&);
    std::string getVariableType(std::string&);

    IRContext* createInstance(std::vector<IRObject::ptr> values);

    bool hasReturnStatement();
    void returnStatementSpotted();

    std::vector<VariablePrototype> functionArgsOrder; // {name_of_arg_1, ..., name_of_arg_n}
private:
    bool hasReturn;
    ContextPrototype* upperContext;

    // variable_name -> (variable_type, variable_name)
    // can be changed to std::map
    std::unordered_map<std::string, VariablePrototype> scopeVariables;
};


#endif //TKOM_INTERPRETER_CONTEXTPROTOTYPE_H
