#ifndef TKOM_INTERPRETER_CONTEXTPROTOTYPE_H
#define TKOM_INTERPRETER_CONTEXTPROTOTYPE_H

#include <string>
#include <map>
#include <utility>

class ContextPrototype {
public:
    typedef std::pair<std::string, std::string> VariablePrototype;
    class VariableNotFound{};

    explicit ContextPrototype(ContextPrototype* upperContext = nullptr) : upperContext(upperContext), hasReturn(false){}

    void addVariable(VariablePrototype&);
    bool isVariableInScope(std::string&);
    std::string getVariableType(std::string&);

    // todo: createContextInstance

    bool hasReturnStatement();
    void returnStatementSpotted();
private:
    bool hasReturn;
    ContextPrototype* upperContext;
    std::map<std::string, VariablePrototype> scopeVariables; // variable name -> (variable_type, variable_name)
};


#endif //TKOM_INTERPRETER_CONTEXTPROTOTYPE_H
