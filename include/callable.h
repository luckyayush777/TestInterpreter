#pragma once

#include<vector>
#include<memory>
#include<string>

#include "token.h" // Provides the Value type

class Environment; // Forward declaration to avoid circular dependencies

class Callable {
    public :
    virtual ~Callable() = default;
    virtual Value call(std::shared_ptr<Environment> executionEnv, const std::vector<Value>& args) = 0;
    virtual size_t arity() const = 0; // Returns the number of parameters the function expects
    virtual std::string toString() const = 0; // For debugging purposes
};