#pragma once

#include <vector>
#include <string>
#include "token.h"

// Forward-declare Environment to avoid including the full header here
class Environment;
class Callable;

// Function declarations
bool isTruthy(const Value& value);
std::string valueToString(const Value& value);
void ShowTokens(const std::vector<Token>& tokens);
const char* tokenTypeToString(TokenType type); // New helper function
