#pragma once
#include <memory>
#include"token.h"
#include"expr.h"
#include"stmt.h"

class Parser{
    const std::vector<Token>& tokens;  
    size_t current = 0;
    
    public :
    Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    std::unique_ptr<Expr> parse()
    {
        return parseExpression();
    }

    std::unique_ptr<Stmt> parseStatement();


    private :
    std::unique_ptr<Stmt> parseVarDeclaration();
    std::unique_ptr<BlockStmt> parseBlock();
    std::unique_ptr<ExprStmt> parseExpressionStmt();
    std::unique_ptr<Expr> parseExpression();
    std::unique_ptr<Expr> parseAssignment();
    std::unique_ptr<Expr> parseAddition();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseFactor();
    bool match(TokenType type);
    bool check(TokenType type);
    bool isAtEnd() const;
    Token consume(TokenType type, const std::string& errorMessage);


    Token advance() {
        if (!isAtEnd()) {
            return tokens[current++];
        }
        return tokens.back(); // Return the last token (EOF)
    }
    const Token& previous() const;
};