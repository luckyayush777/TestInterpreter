#pragma once

#include <vector>
#include<memory>
#include<iostream>

#include"expr.h"

class Stmt{
    public :
    virtual ~Stmt() = default;
    virtual void execute() = 0;
};

class ExprStmt : public Stmt{
    public :
    std::unique_ptr<Expr> expression;
    ExprStmt(std::unique_ptr<Expr> expr) : expression(std::move(expr)) {}

    void execute() override {
        // For now, just evaluate the expression and discard the result
        std::cout<<"Result : " << expression->evaluate()<<" \n";
        // In a full interpreter, you might want to store the result or do something with it
        // For example, you could print it or store it in a variable
        // Here, we just print it to the console
        // This is a placeholder for future functionality
    }
};

class BlockStmt : public Stmt{
    public :
    std::vector<std::unique_ptr<Stmt>> statements;

    BlockStmt(std::vector<std::unique_ptr<Stmt>> stmts) 
        : statements(std::move(stmts)) {}

    void execute() override {
        for (auto& stmt : statements) {
            stmt->execute();
        }
    }

    void addStatement(std::unique_ptr<Stmt> stmt) {
        statements.push_back(std::move(stmt));
    }
};

