#pragma once

#include <string>
#include <vector>

// Ensure TokenType is only defined here and not elsewhere
enum class TokenType{
    NUMBER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    INVALID,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    END_OF_FILE
};
struct Token {
    TokenType type;
    std::string lexeme;

    //doesnt make sense for some types of tokens
    //but is useful for NUMBER tokens
    double numberValue = 0.0;

    Token(TokenType type, std::string lexeme) : type(type), lexeme(std::move(lexeme)) {}
    Token(TokenType type, std::string lexeme, double numberValue) 
        : type(type), lexeme(std::move(lexeme)), numberValue(numberValue) {}
};
