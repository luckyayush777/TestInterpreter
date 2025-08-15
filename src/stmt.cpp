#include"stmt.h"
#include"function.h"
#include<memory>

void FunctionStmt::execute(std::shared_ptr<Environment> env) {
    auto function = std::make_shared<Function>(this, env);
    env->define(name.lexeme, function);
}