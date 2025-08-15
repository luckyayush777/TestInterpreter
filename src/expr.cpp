#include "expr.h"
#include "environment.h" 
#include"callable.h"

// Need the full definition for evaluate methods
#include <stdexcept>

#include"util.h" // For isTruthy and valueToString
// --- Implementation for LiteralExpr ---
Value LiteralExpr::evaluate(std::shared_ptr<Environment> env) {
    return value;
}

// --- Implementation for VariableExpr ---
Value VariableExpr::evaluate(std::shared_ptr<Environment> env) {
    return env->get(name.lexeme);
}

// --- Implementation for AssignmentExpr ---
Value AssignmentExpr::evaluate(std::shared_ptr<Environment> env) {
    Value val = value->evaluate(env);
    env->assign(name.lexeme, val);
    return val;
}


Value UnaryExpr::evaluate(std::shared_ptr<Environment> env) {
    Value rightValue = right->evaluate(env);

    switch (op.type) {
        case TokenType::MINUS:
            // Ensure the operand is a number before negating
            if (std::holds_alternative<double>(rightValue)) {
                return -std::get<double>(rightValue);
            }
            throw std::runtime_error("Operand must be a number for '-' operator.");
        case TokenType::BANG:
            // The '!' operator inverts the "truthiness" of a value
            return !isTruthy(rightValue);
        default:
            // Should be unreachable if the parser is correct
            throw std::runtime_error("Invalid unary operator.");
    }
}
// --- Implementation for BinaryExpr ---

// Helper function to check if both variants hold doubles
void checkNumberOperands(const Token& op, const Value& left, const Value& right) {
    if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
        return;
    }
    throw std::runtime_error("Operands must be numbers for operator '" + op.lexeme + "'.");
}

Value BinaryExpr::evaluate(std::shared_ptr<Environment> env) {
    Value leftValue = left->evaluate(env);
    Value rightValue = right->evaluate(env);

    switch (op.type) {
        // Comparison Operators
        case TokenType::GREATER_THAN:
            checkNumberOperands(op, leftValue, rightValue);
            return std::get<double>(leftValue) > std::get<double>(rightValue);
        case TokenType::GREATER_THAN_EQUALS:
            checkNumberOperands(op, leftValue, rightValue);
            return std::get<double>(leftValue) >= std::get<double>(rightValue);
        case TokenType::LESS_THAN:
            checkNumberOperands(op, leftValue, rightValue);
            return std::get<double>(leftValue) < std::get<double>(rightValue);
        case TokenType::LESS_THAN_EQUALS:
            checkNumberOperands(op, leftValue, rightValue);
            return std::get<double>(leftValue) <= std::get<double>(rightValue);

        // Equality Operators
        case TokenType::BANG_EQUALS:
            return leftValue != rightValue;
        case TokenType::EQUALS_EQUALS:
            return leftValue == rightValue;

        // Arithmetic Operators
        case TokenType::MINUS:
            checkNumberOperands(op, leftValue, rightValue);
            return std::get<double>(leftValue) - std::get<double>(rightValue);
        case TokenType::PLUS:
            if (std::holds_alternative<double>(leftValue) && std::holds_alternative<double>(rightValue)) {
                return std::get<double>(leftValue) + std::get<double>(rightValue);
            }
            if (std::holds_alternative<std::string>(leftValue) && std::holds_alternative<std::string>(rightValue)) {
                return std::get<std::string>(leftValue) + std::get<std::string>(rightValue);
            }
            throw std::runtime_error("Operands must be two numbers or two strings for '+'.");
        
        case TokenType::SLASH:
            checkNumberOperands(op, leftValue, rightValue);
            if (std::get<double>(rightValue) == 0.0) {
                throw std::runtime_error("Division by zero.");
            }
            return std::get<double>(leftValue) / std::get<double>(rightValue);
        case TokenType::STAR:
            checkNumberOperands(op, leftValue, rightValue);
            return std::get<double>(leftValue) * std::get<double>(rightValue);

        default:
            // This case should ideally be unreachable if the parser is correct.
            throw std::runtime_error("Invalid binary operator.");
    }
}

Value CallExpr::evaluate(std::shared_ptr<Environment> env) {
    Value calleeValue = callee->evaluate(env);
    std::vector<Value> args;
    for (const auto& arg : arguments) {
        args.push_back(arg->evaluate(env));
    }
    if (!std::holds_alternative<std::shared_ptr<Callable>>(calleeValue)) {
        throw std::runtime_error("Callee is not callable.");
    }

    auto function = std::get<std::shared_ptr<Callable>>(calleeValue);
    if(args.size() != function->arity()) {
        throw std::runtime_error("Expected " + std::to_string(function->arity()) + 
        " arguments but got " + std::to_string(args.size()) + ".");
    }
    if (args.size() > 255) {
        throw std::runtime_error("Cannot have more than 255 arguments.");
    }

    return function->call(env, args);
}
