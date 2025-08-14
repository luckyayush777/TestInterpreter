#include "util.h"
#include <iostream>
#include <variant>

// Implementation for isTruthy with std::variant
bool isTruthy(const Value& value) {
    if (std::holds_alternative<std::nullptr_t>(value)) return false;
    if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
    if (std::holds_alternative<double>(value)) return std::get<double>(value) != 0.0;
    return true; // All other types (like strings) are truthy
}

// Helper function to convert a Value variant to a string for printing
std::string valueToString(const Value& value) {
    if (std::holds_alternative<std::nullptr_t>(value)) {
        return "nil";
    }
    if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? "true" : "false";
    }
    if (std::holds_alternative<double>(value)) {
        return std::to_string(std::get<double>(value));
    }
    if (std::holds_alternative<std::string>(value)) {
        return std::get<std::string>(value);
    }
    return "unknown value type";
}

// ShowTokens remains largely the same, but we can update it to show literals
void ShowTokens(const std::vector<Token>& tokens) {
    for (const Token& t : tokens) {
        std::cout << "Token: " << t.lexeme << " Type: " << static_cast<int>(t.type);
        if (t.type == TokenType::NUMBER || t.type == TokenType::STRING) {
            std::cout << " Literal: " << valueToString(t.literal);
        }
        std::cout << '\n';
    }
}
