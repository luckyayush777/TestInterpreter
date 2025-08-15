#pragma once

#include <string> 
#include <vector>
#include <variant>

// This is the single, canonical definition of the Value type.
using Value = std::variant<std::nullptr_t, bool, double, std::string, std::shared_ptr<class Callable>>;

enum class TokenType{
    NUMBER, PLUS, MINUS, STAR, SLASH, INVALID, LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE, EQUALS, EQUALS_EQUALS, LESS_THAN,
    LESS_THAN_EQUALS, GREATER_THAN, GREATER_THAN_EQUALS, BANG, BANG_EQUALS,
    IDENTIFIER, STRING, NUMBER_LITERAL, IF, ELSE, WHILE, FOR, FUNCTION,
    RETURN, VAR, NIL, TRUE, PRINT, FALSE, AND, OR, SEMICOLON, END_OF_FILE,COMMA
};

struct Token {
    TokenType type;
    std::string lexeme;
    Value literal; // Replaces numberValue

    // Constructor for non-literal tokens
    Token(TokenType type, std::string lexeme) 
        : type(type), lexeme(std::move(lexeme)), literal{nullptr} {} // Corrected initializer

    // Constructor for literal tokens
    Token(TokenType type, std::string lexeme, Value literal) 
        : type(type), lexeme(std::move(lexeme)), literal(std::move(literal)) {}
};
