#include "function.h"
#include "stmt.h" // For ReturnValue

// --- Implementation for the Function class ---

Value Function::call(std::shared_ptr<Environment> executionEnv, const std::vector<Value>& args) {
    // 1. Create a new environment for the function's body.
    // The parent of this environment is the function's closure,
    // which enables lexical scoping.
    auto environment = std::make_shared<Environment>(closure);

    // 2. Bind the arguments to the function's parameters.
    for (size_t i = 0; i < declaration->params.size(); ++i) {
        environment->define(declaration->params[i].lexeme, args[i]);
    }

    // 3. Execute the function body.
    try {
        for (const auto& stmt : declaration->body) {
            stmt->execute(environment);
        }
    } catch (const ReturnValue& returnValue) {
        // A 'return' was hit. We caught it, so now we can return its value.
        return returnValue.value;
    }

    // If no 'return' was hit, implicitly return nil.
    return nullptr;
}