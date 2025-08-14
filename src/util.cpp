#include "util.h"
#include <iostream>
#include <variant>

// New helper function to convert TokenType enum to a string
const char* tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::STAR: return "STAR";
        case TokenType::SLASH: return "SLASH";
        case TokenType::INVALID: return "INVALID";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::EQUALS: return "EQUALS";
        case TokenType::EQUALS_EQUALS: return "EQUALS_EQUALS";
        case TokenType::LESS_THAN: return "LESS_THAN";
        case TokenType::LESS_THAN_EQUALS: return "LESS_THAN_EQUALS";
        case TokenType::GREATER_THAN: return "GREATER_THAN";
        case TokenType::GREATER_THAN_EQUALS: return "GREATER_THAN_EQUALS";
        case TokenType::BANG: return "BANG";
        case TokenType::BANG_EQUALS: return "BANG_EQUALS";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::IF: return "IF";
        case TokenType::ELSE: return "ELSE";
        case TokenType::WHILE: return "WHILE";
        case TokenType::FOR: return "FOR";
        case TokenType::FUNCTION: return "FUNCTION";
        case TokenType::RETURN: return "RETURN";
        case TokenType::VAR: return "VAR";
        case TokenType::NIL: return "NIL";
        case TokenType::TRUE: return "TRUE";
        case TokenType::PRINT: return "PRINT";
        case TokenType::FALSE: return "FALSE";
        case TokenType::AND: return "AND";
        case TokenType::OR: return "OR";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        default: return "UNKNOWN";
    }
}

// Implementation for isTruthy with std::variant
bool isTruthy(const Value& value) {
    if (std::holds_alternative<std::nullptr_t>(value)) return false;
    if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
    if (std::holds_alternative<double>(value)) return std::get<double>(value) != 0.0;
    return true; // All other types (like strings) are truthy
}

// Helper function to convert a Value variant to a string for printing
std::string valueToString(const Value& value) {
    if (std::holds_alternative<std::nullptr_t>(value)) return "nil";
    if (std::holds_alternative<bool>(value)) return std::get<bool>(value) ? "true" : "false";
    if (std::holds_alternative<double>(value)) return std::to_string(std::get<double>(value));
    if (std::holds_alternative<std::string>(value)) return std::get<std::string>(value);
    return "unknown value type";
}

// Updated ShowTokens to be more readable
void ShowTokens(const std::vector<Token>& tokens) {
    std::cout << "--- TOKENS ---" << std::endl;
    for (const Token& t : tokens) {
        // Print the token type as a string
        std::cout << "Type: " << tokenTypeToString(t.type);
        // Pad the output for alignment
        std::cout << "\tLexeme: '" << t.lexeme << "'";
        // Only print the literal if it's not nil
        if (!std::holds_alternative<std::nullptr_t>(t.literal)) {
            std::cout << "\tLiteral: " << valueToString(t.literal);
        }
        std::cout << std::endl;
    }
    std::cout << "-----END---------" << std::endl;
}
