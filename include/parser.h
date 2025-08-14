#pragma once
#include <memory>
#include <vector>
#include "token.h"
#include "expr.h"
#include "stmt.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens) {}
    std::vector<std::unique_ptr<Stmt>> parse();

private:
    // Statement parsing
    std::unique_ptr<Stmt> parseStatement();
    std::unique_ptr<Stmt> parsePrintStatement();
    std::unique_ptr<Stmt> parseIfStatement();
    std::unique_ptr<Stmt> parseVarDeclaration();
    std::unique_ptr<Stmt> parseExpressionStmt();
    std::unique_ptr<BlockStmt> parseBlock();

    // Expression parsing (in order of precedence)
    std::unique_ptr<Expr> parseExpression();
    std::unique_ptr<Expr> parseAssignment();
    std::unique_ptr<Expr> parseEquality();
    std::unique_ptr<Expr> parseComparison();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseFactor();
    std::unique_ptr<Expr> parseUnary();
    std::unique_ptr<Expr> parsePrimary();

    // Helper methods
    bool match(const std::vector<TokenType>& types);
    bool check(TokenType type) const;
    bool isAtEnd() const;
    Token advance();
    const Token& peek() const;
    const Token& previous() const;
    Token consume(TokenType type, const std::string& errorMessage);

    const std::vector<Token>& tokens;
    size_t current = 0;
};
