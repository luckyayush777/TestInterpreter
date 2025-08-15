#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "expr.h"
#include "environment.h"
#include "util.h" // For isTruthy and the new valueToString helper

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
        // We need a helper to print the variant
        expression->evaluate(env);
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
};

class VarStmt : public Stmt{
    public :
    Token name;
    std::unique_ptr<Expr> initializer;

    VarStmt(Token name, std::unique_ptr<Expr> initializer = nullptr)
        : name(std::move(name)), initializer(std::move(initializer)) {}

    void execute(std::shared_ptr<Environment> env) override {
        Value value = nullptr; // Default value is now nil
        if (initializer) {
            value = initializer->evaluate(env);
        }
        env->define(name.lexeme, value);
    }
};

class IfStmt : public Stmt {
    public :
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> thenBranch;
    std::unique_ptr<Stmt> elseBranch;   

    IfStmt(std::unique_ptr<Expr> cond, std::unique_ptr<Stmt> thenB, 
           std::unique_ptr<Stmt> elseB = nullptr)
        : condition(std::move(cond)), thenBranch(std::move(thenB)), 
          elseBranch(std::move(elseB)) {}

    void execute(std::shared_ptr<Environment> env) override{
        if (isTruthy(condition->evaluate(env))) {
            thenBranch->execute(env);
        } else if (elseBranch) {
            elseBranch->execute(env);
        }
    }
};

class WhileStmt : public Stmt {
    public :
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> body;

    WhileStmt(std::unique_ptr<Expr> cond, std::unique_ptr<Stmt> b)
        : condition(std::move(cond)), body(std::move(b)) {}

    void execute(std::shared_ptr<Environment> env) override {
        while (isTruthy(condition->evaluate(env))) {
            body->execute(env);
        }
    }
};

class FunctionStmt : public Stmt {
    public :
    Token name;
    std::vector<Token> params; // Function parameters
    std::vector<std::unique_ptr<Stmt>> body; // vector of statements in the function body

    FunctionStmt(Token name, std::vector<Token> params, std::vector<std::unique_ptr<Stmt>> body)
        : name(std::move(name)), params(std::move(params)), body(std::move(body)) {}

    void execute(std::shared_ptr<Environment> env) override;
};

class ReturnStmt : public Stmt {
    public :
    Token keyword; // The 'return' keyword token
    std::unique_ptr<Expr> value; // The return value expression

    ReturnStmt(Token keyword, std::unique_ptr<Expr> value) : 
        keyword(std::move(keyword)), value(std::move(value)) {}

    void execute(std::shared_ptr<Environment> env) override {
        Value val = nullptr;
        if (value) {
            throw ReturnValue(value->evaluate(env));
        } else {
            throw ReturnValue(nullptr); // Return nil if no value is provided
        }
    }
};
class PrintStmt : public Stmt {
    public :
    std::unique_ptr<Expr> expression;

    PrintStmt(std::unique_ptr<Expr> expr) : expression(std::move(expr)) {}

    void execute(std::shared_ptr<Environment> env) override {
        Value value = expression->evaluate(env);
        std::cout << valueToString(value) << std::endl;
    }
};


struct ReturnValue{
    Value value;

    explicit ReturnValue(Value val) : value(std::move(val)) {}
};



