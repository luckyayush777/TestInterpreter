#pragma once

#include"lexer.h"

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        char c = advance();

        switch (c) {
            case ' ':
            case '\t':
            case '\n':
                // Ignore whitespace
                break;
            case '+':
                tokens.emplace_back(TokenType::PLUS, "+");
                break;
            case '-':
                tokens.emplace_back(TokenType::MINUS, "-");
                break;
            case '*':
                tokens.emplace_back(TokenType::STAR, "*");
                break;
            case '/':
                tokens.emplace_back(TokenType::SLASH, "/");
                break;
            case '(':
                tokens.emplace_back(TokenType::LEFT_PAREN, "(");
                break;
            case ')':
                tokens.emplace_back(TokenType::RIGHT_PAREN, ")");
                break;
            default:
                if (isdigit(c) || (c == '.')) {
                    tokens.push_back(number(c));
                } else {
                    tokens.emplace_back(TokenType::INVALID, std::string(1, c));
                }
        }
    }
    tokens.emplace_back(TokenType::END_OF_FILE, ""); // End of input token
    return tokens;
}
