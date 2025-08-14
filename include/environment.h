#pragma once
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "token.h" // Include for the Value type definition

class Environment {
private:
    std::unordered_map<std::string, Value> values;
    std::shared_ptr<Environment> enclosing;

public :
    Environment(std::shared_ptr<Environment> parent = nullptr);
    void define(const std::string& name, const Value& val);
    void assign(const std::string& name, const Value& val);
    Value get(const std::string& name) const;
};
