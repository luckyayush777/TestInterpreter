#pragma once
#include <memory>
#include"token.h"
#include"expr.h"

class Parser{
    const std::vector<Token>& tokens;  
    size_t current = 0;
    
    public :
    Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    std::unique_ptr<Expr> parse()
    {
        return parseExpression();
    }

    private :
    std::unique_ptr<Expr> parseExpression();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseFactor();
    bool match(TokenType type);
    bool check(TokenType type);
    bool isAtEnd() const;
    const Token& previous() const;
};