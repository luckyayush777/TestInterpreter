#include "environment.h"

Environment::Environment(std::shared_ptr<Environment> parent) : enclosing(parent) {}
\
void Environment::define(const std::string& name, const Value& val) {
    values[name] = val;
}

// Corrected to take 'const Value&' to match the header
void Environment::assign(const std::string& name, const Value& val) {
    if (values.count(name)) {
        values[name] = val;
        return;
    }
    
    if (enclosing) {
        enclosing->assign(name, val);
        return;
    }
    
    throw std::runtime_error("Undefined variable '" + name + "'");
}

Value Environment::get(const std::string& name) const {
    if (values.count(name)) {
        return values.at(name);
    }
    
    if (enclosing) {
        return enclosing->get(name);
    }
    
    throw std::runtime_error("Undefined variable '" + name + "'");
}
