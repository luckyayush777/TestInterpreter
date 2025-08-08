#pragma once
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <unordered_map>

using Value = double; // Define Value as a double for simplicity

class Environment {
private:
    std::unordered_map<std::string, Value> values;
    std::shared_ptr<Environment> enclosing;

public :
    Environment(std::shared_ptr<Environment> parent = nullptr);
    void define(const std::string& name, Value val);
    void assign(const std::string& name, Value val);
    Value get(const std::string& name) const;

};