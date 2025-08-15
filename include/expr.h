#pragma once
#include <memory>

#include "token.h" // Provides the Value type
// Forward declaration of Environment to avoid circular dependencies
class Environment;

// The base class for all expression AST nodes.
struct Expr {
    virtual Value evaluate(std::shared_ptr<Environment> env) = 0;
    virtual ~Expr() = default;
};


// NEW: Represents a unary operation like '-' or '!'.
struct UnaryExpr : public Expr {
    Token op;
    std::unique_ptr<Expr> right;

    UnaryExpr(Token op, std::unique_ptr<Expr> right)
        : op(std::move(op)), right(std::move(right)) {}

    Value evaluate(std::shared_ptr<Environment> env) override; // Implementation in expr.cpp
};
// A general expression for literal values (numbers, true, false, nil).
struct LiteralExpr : public Expr {
    Value value;

    explicit LiteralExpr(Value val) : value(std::move(val)) {}

    Value evaluate(std::shared_ptr<Environment> env) override; // Implementation in expr.cpp
};

// Represents a binary operation.
struct BinaryExpr : public Expr {
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    Token op;

    BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    Value evaluate(std::shared_ptr<Environment> env) override; // Implementation in expr.cpp
};

// Represents a variable lookup.
struct VariableExpr : public Expr {
    Token name;
    VariableExpr(Token name) : name(std::move(name)) {}
    Value evaluate(std::shared_ptr<Environment> env) override; // Implementation in expr.cpp
};

// Represents a variable assignment.
struct AssignmentExpr : public Expr {
    Token name;
    std::unique_ptr<Expr> value;

    AssignmentExpr(Token name, std::unique_ptr<Expr> value)
        : name(std::move(name)), value(std::move(value)) {}

    Value evaluate(std::shared_ptr<Environment> env) override; // Implementation in expr.cpp
};

struct CallExpr : public Expr {
    std::unique_ptr<Expr> callee; // This can be any expression
    Token paren; // The closing parenthesis for error reporting
    std::vector<std::unique_ptr<Expr>> arguments;

    CallExpr(std::unique_ptr<Expr> callee, Token paren, std::vector<std::unique_ptr<Expr>> arguments)
        : callee(std::move(callee)), paren(std::move(paren)), arguments(std::move(arguments)) {}

    Value evaluate(std::shared_ptr<Environment> env) override;
};
