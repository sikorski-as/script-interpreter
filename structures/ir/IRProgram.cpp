#include "IRProgram.h"

void IRProgram::run() {
    auto context = definedFunctions["main"]->contextProto.createInstance({});
    context->definedFunctions = definedFunctions;

    definedFunctions["main"]->execute(context, {});
}
