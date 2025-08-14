#pragma once
#include <memory>
#include <variant>
#include <string>

#include "token.h"
#include "environment.h"



// The base class for all expression AST nodes.
struct Expr {
    virtual Value evaluate(std::shared_ptr<Environment> env) = 0;
    virtual ~Expr() = default;
};


// A new, more general expression for literal values (numbers, true, false, nil).
struct LiteralExpr : public Expr {
    Value value;

    explicit LiteralExpr(Value val) : value(std::move(val)) {}

    Value evaluate(std::shared_ptr<Environment> env) override {
        return value;
    }
};

// Represents a binary operation.
struct BinaryExpr : public Expr {
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    Token op;

    BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    // This now needs to handle different types and return a variant.
    Value evaluate(std::shared_ptr<Environment> env) override;
};

// Represents a variable lookup.
struct VariableExpr : public Expr {
    Token name;
    VariableExpr(Token name) : name(std::move(name)) {}
    Value evaluate(std::shared_ptr<Environment> env) override {
        return env->get(name.lexeme);
    }
};

// Represents a variable assignment.
struct AssignmentExpr : public Expr {
    Token name;
    std::unique_ptr<Expr> value;

    AssignmentExpr(Token name, std::unique_ptr<Expr> value)
        : name(std::move(name)), value(std::move(value)) {}

    Value evaluate(std::shared_ptr<Environment> env) override {
        Value val = value->evaluate(env);
        env->assign(name.lexeme, val);
        return val;
    }
};
