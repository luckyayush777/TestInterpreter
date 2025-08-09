#pragma once

#include <vector>
#include<memory>
#include<iostream>

#include"expr.h"
#include"environment.h"

class Stmt{
    public :
    virtual ~Stmt() = default;
    virtual void execute(std::shared_ptr<Environment> env) = 0;
};

class ExprStmt : public Stmt{
    public :
    std::unique_ptr<Expr> expression;
    ExprStmt(std::unique_ptr<Expr> expr) : expression(std::move(expr)) {}

    void execute(std::shared_ptr<Environment> env) override {
        // For now, just evaluate the expression and discard the result
        std::cout<<"Result : " << expression->evaluate(env)<<" \n";
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

    void execute(std::shared_ptr<Environment> env) override {
        auto blockEnv = std::make_shared<Environment>(env);
        for (auto& stmt : statements) {
            stmt->execute(blockEnv);
        }
    }

    void addStatement(std::unique_ptr<Stmt> stmt) {
        statements.push_back(std::move(stmt));
    }
};

class VarStmt : public Stmt{
    public :
    Token name;
    std::unique_ptr<Expr> initializer;

    VarStmt(Token name, std::unique_ptr<Expr> initializer = nullptr)
        : name(std::move(name)), initializer(std::move(initializer)) {}

    void execute(std::shared_ptr<Environment> env) override {
        Value value = 0.0; // Default value
        if (initializer) {
            value = initializer->evaluate(env);
        }
        env->define(name.lexeme, value);
    }
};

