#include"parser.h"


std::unique_ptr<BlockStmt> Parser::parseBlock() {
    std::vector<std::unique_ptr<Stmt>> statements;
    while (!isAtEnd() && !check(TokenType::RIGHT_BRACE)) {      
        statements.push_back(parseStatement());
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' to close block");
    return std::make_unique<BlockStmt>(std::move(statements));
}

std::unique_ptr<ExprStmt> Parser::parseExpressionStmt() {
    auto expr = parseExpression();
    consume(TokenType::SEMICOLON, "Expected ';' after expression");
    return std::make_unique<ExprStmt>(std::move(expr));
}

std::unique_ptr<Stmt> Parser::parseStatement() {
    if(match(TokenType::LEFT_BRACE)) {
        return parseBlock();
    }
    if (match(TokenType::SEMICOLON)) {
        return std::make_unique<ExprStmt>(nullptr); // Empty statement
    }
    return parseExpressionStmt();
}

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

Token Parser::consume(TokenType type, const std::string& errorMessage) {
    if (check(type)) {
        return advance();
    }
    throw std::runtime_error(errorMessage + " Found: " + previous().lexeme);
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