#ifndef TKOM_INTERPRETER_IRSTATEMENT_H
#define TKOM_INTERPRETER_IRSTATEMENT_H

#include <memory>
#include <vector>
#include "IRExecutable.h"

class IRStatement : public IRExecutable{
public:
    typedef std::shared_ptr<IRStatement> ptr;
    typedef std::vector<IRStatement::ptr> StatementsList;
};


#endif //TKOM_INTERPRETER_IRSTATEMENT_H
