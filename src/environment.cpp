#include"environment.h"


Environment::Environment(std::shared_ptr<Environment> parent) : enclosing(parent) {}
void Environment::define(const std::string& name, Value val) {
    values[name] = val;
}

void Environment::assign(const std::string& name, Value val) {
    if(values.count(name))
    {
        values[name] = val;
    } else if (enclosing) {
        enclosing->assign(name, val);
    } else {
        throw std::runtime_error("Undefined variable '" + name + "'");
    }
}

Value Environment::get(const std::string& name) const {
    if(values.count(name)) {
        return values.at(name);
    } else if (enclosing) {
        return enclosing->get(name);
    } else {
        throw std::runtime_error("Undefined variable '" + name + "'");
    }
}