#include"parser.h"

std::unique_ptr<Expr> Parser::parseExpression() {
    auto left = parseTerm();

    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        TokenType op = previous().type;
        auto right = parseTerm();
        left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
    }

    return left;
}

std::unique_ptr<Expr> Parser::parseTerm() {
    auto left = parseFactor();

    while (match(TokenType::STAR) || match(TokenType::SLASH)) {
        TokenType op = previous().type;
        auto right = parseFactor();
        left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
    }

    return left;
}

std::unique_ptr<Expr> Parser::parseFactor() {
    if (match(TokenType::NUMBER)) {
        return std::make_unique<NumberExpr>(previous().numberValue);
    }

    if (match(TokenType::LEFT_PAREN)) {
        auto expr = parseExpression();
        if (!match(TokenType::RIGHT_PAREN)) {
            throw std::runtime_error("Expected ')' after expression");
        }
        return expr;
    }

    throw std::runtime_error("Expected number or '('");
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        current++;
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return tokens[current].type == type;
}

bool Parser::isAtEnd() const {
    return current >= tokens.size() || tokens[current].type == TokenType::END_OF_FILE;
}

const Token& Parser::previous() const {
    if (current == 0) {
        throw std::runtime_error("No previous token");
    }
    return tokens[current - 1];
}