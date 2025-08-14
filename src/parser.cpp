#include "parser.h"
#include <vector>

// Main entry point: Parses a sequence of statements.
std::vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> statements;
    while (!isAtEnd()) {
        statements.push_back(parseStatement());
    }
    return statements;
}

//-- STATEMENT PARSING --//

std::unique_ptr<Stmt> Parser::parseStatement() {
    if(match({TokenType::PRINT})) return parsePrintStatement();
    if (match({TokenType::IF})) return parseIfStatement();
    if (match({TokenType::VAR})) return parseVarDeclaration();
    if (match({TokenType::LEFT_BRACE})) return parseBlock();

     if (check(TokenType::END_OF_FILE)) return nullptr; 
    return parseExpressionStmt();
}

std::unique_ptr<Stmt> Parser::parsePrintStatement() {
    auto expr = parseExpression();
    consume(TokenType::SEMICOLON, "Expected ';' after print statement.");
    return std::make_unique<PrintStmt>(std::move(expr));
}

std::unique_ptr<Stmt> Parser::parseIfStatement() {
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'if'.");
    auto condition = parseExpression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after if condition.");

    auto thenBranch = parseStatement();
    std::unique_ptr<Stmt> elseBranch = nullptr;
    if (match({TokenType::ELSE})) {
        elseBranch = parseStatement();
    }
    return std::make_unique<IfStmt>(std::move(condition), std::move(thenBranch), std::move(elseBranch));
}

std::unique_ptr<BlockStmt> Parser::parseBlock() {
    std::vector<std::unique_ptr<Stmt>> statements;
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        statements.push_back(parseStatement());
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");
    return std::make_unique<BlockStmt>(std::move(statements));
}

std::unique_ptr<Stmt> Parser::parseVarDeclaration() {
    Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");
    std::unique_ptr<Expr> initializer = nullptr;
    if (match({TokenType::EQUALS})) {
        initializer = parseExpression();
    }
    consume(TokenType::SEMICOLON, "Expected ';' after variable declaration.");
    return std::make_unique<VarStmt>(name, std::move(initializer));
}

std::unique_ptr<Stmt> Parser::parseExpressionStmt() {
    auto expr = parseExpression();
    consume(TokenType::SEMICOLON, "Expected ';' after expression.");
    return std::make_unique<ExprStmt>(std::move(expr));
}


//-- EXPRESSION PARSING (by precedence) --//

std::unique_ptr<Expr> Parser::parseExpression() {
    return parseAssignment();
}

std::unique_ptr<Expr> Parser::parseAssignment() {
    auto expr = parseEquality(); // Next lowest precedence
    if (match({TokenType::EQUALS})) {
        Token equals = previous();
        auto value = parseAssignment(); // Right-associative
        if (auto* varExpr = dynamic_cast<VariableExpr*>(expr.get())) {
            return std::make_unique<AssignmentExpr>(varExpr->name, std::move(value));
        }
        throw std::runtime_error("Invalid assignment target.");
    }
    return expr;
}

// In parser.cpp

// Handles ! and - (prefix)
std::unique_ptr<Expr> Parser::parseUnary() {
    if (match({TokenType::BANG, TokenType::MINUS})) {
        Token op = previous();
        auto right = parseUnary();
        // This is now active and will create the UnaryExpr node
        return std::make_unique<UnaryExpr>(op, std::move(right));
    }
    return parsePrimary();
}



// NEW: Handles == and !=
std::unique_ptr<Expr> Parser::parseEquality() {
    auto expr = parseComparison(); // Next higher precedence
    while (match({TokenType::BANG_EQUALS, TokenType::EQUALS_EQUALS})) {
        Token op = previous();
        auto right = parseComparison();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }
    return expr;
}

// NEW: Handles >, >=, <, <=
std::unique_ptr<Expr> Parser::parseComparison() {
    auto expr = parseTerm(); // Next higher precedence
    while (match({TokenType::GREATER_THAN, TokenType::GREATER_THAN_EQUALS, 
        TokenType::LESS_THAN, TokenType::LESS_THAN_EQUALS})) {
        Token op = previous();
        auto right = parseTerm();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }
    return expr;
}

// Handles + and -
std::unique_ptr<Expr> Parser::parseTerm() {
    auto expr = parseFactor();
    while (match({TokenType::MINUS, TokenType::PLUS})) {
        Token op = previous();
        auto right = parseFactor();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }
    return expr;
}

// Handles * and /
std::unique_ptr<Expr> Parser::parseFactor() {
    auto expr = parseUnary();
    while (match({TokenType::SLASH, TokenType::STAR})) {
        Token op = previous();
        auto right = parseUnary();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }
    return expr;
}


// Handles literals and grouping
std::unique_ptr<Expr> Parser::parsePrimary() {
    if (match({TokenType::FALSE})) return std::make_unique<LiteralExpr>(false);
    if (match({TokenType::TRUE})) return std::make_unique<LiteralExpr>(true);
    if (match({TokenType::NIL})) return std::make_unique<LiteralExpr>(nullptr);

    if (match({TokenType::NUMBER, TokenType::STRING})) {
        return std::make_unique<LiteralExpr>(previous().literal);
    }

    if (match({TokenType::IDENTIFIER})) {
        return std::make_unique<VariableExpr>(previous());
    }

    if (match({TokenType::LEFT_PAREN})) {
        auto expr = parseExpression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");
        // You'll need a GroupingExpr class in expr.h for this
        // return std::make_unique<GroupingExpr>(std::move(expr));
        return expr;
    }

    throw std::runtime_error("Expected expression.");
}


//-- HELPER METHODS --//

bool Parser::match(const std::vector<TokenType>& types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    throw std::runtime_error(message);
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::END_OF_FILE;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::previous() const {
    return tokens[current - 1];
}
