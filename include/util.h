#pragma once

#include <vector>
#include <string>
#include "token.h"
#include "environment.h"

// Function declarations
bool isTruthy(const Value& value);
std::string valueToString(const Value& value);
void ShowTokens(const std::vector<Token>& tokens);
