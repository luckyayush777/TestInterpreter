#pragma once

#include <memory>
#include<vector>

#include"callable.h"
#include"stmt.h"
#include"environment.h"

class BlockStmt; // Forward declaration to avoid circular dependencies

class Function : public Callable {
    private : 
    FunctionStmt* declaration;
    std::shared_ptr<Environment> closure; // The environment where the function was defined

    public :
    Function(FunctionStmt* declaration, std::shared_ptr<Environment> closure) :
        declaration(declaration), closure(std::move(closure)) {}

    size_t arity() const override {
        return declaration->params.size();
    }

    Value call(std::shared_ptr<Environment> executionEnv, const std::vector<Value>& args) override;

    std::string toString() const override {
        return "<fn " + declaration->name.lexeme + ">";
    }

};