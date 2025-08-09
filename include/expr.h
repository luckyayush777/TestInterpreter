#pragma once
#include <memory>


#include"token.h"
#include"environment.h"

struct Expr{
    virtual Value evaluate(std::shared_ptr<Environment> env) = 0;
    virtual ~Expr() = default;
};

struct NumberExpr : public Expr{
    double value;

    explicit NumberExpr(double value) : value(value) {}

    double evaluate(std::shared_ptr<Environment> env) override {
        return value;
    }
};

struct BinaryExpr : public Expr{
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    TokenType op;

    BinaryExpr(std::unique_ptr<Expr> left, TokenType op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
    Value evaluate(std::shared_ptr<Environment> env) override {
        Value leftValue = left->evaluate(env);
        Value rightValue = right->evaluate(env);
        switch(op){
            case TokenType::PLUS: return leftValue + rightValue;
            case TokenType::MINUS: return leftValue - rightValue;
            case TokenType::STAR: return leftValue * rightValue;
            case TokenType::SLASH: 
                if (rightValue == 0) {
                    throw std::runtime_error("Division by zero");
                }
                return leftValue / rightValue;
            default:
                throw std::runtime_error("Invalid operator");
        }
    }
};

struct VariableExpr : public Expr{
    Token name;
    VariableExpr(Token name) : name(std::move(name)) {}
    Value evaluate(std::shared_ptr<Environment> env) override {
        return env->get(name.lexeme);
    }
};

struct AssignmentExpr : public Expr{
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



