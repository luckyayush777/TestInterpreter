#pragma once
#include <memory>

#include"token.h"
struct Expr{
    virtual double evaluate() = 0;
    virtual ~Expr() = default;
};

struct NumberExpr : public Expr{
    double value;

    explicit NumberExpr(double value) : value(value) {}

    double evaluate() override {
        return value;
    }
};

struct BinaryExpr : public Expr{
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    TokenType op;

    BinaryExpr(std::unique_ptr<Expr> left, TokenType op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
    double evaluate() override {
        double leftValue = left->evaluate();
        double rightValue = right->evaluate();
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



