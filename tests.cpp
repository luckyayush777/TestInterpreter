#include "lexer.h"
#include "parser.h"
#include "expr.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <cmath> // for std::fabs

void runTest(const std::string& input, double expected) {
    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    std::unique_ptr<Expr> expression = parser.parse();

    double result = expression->evaluate();

    // Allow some floating-point wiggle
    if (std::fabs(result - expected) > 1e-9) {
        std::cerr << "FAILED: " << input << " → got " << result << ", expected " << expected << "\n";
        assert(false);
    } else {
        std::cout << "PASS: " << input << " = " << result << "\n";
    }
}

int main() {
    runTest("1 + 2 * 3", 7);
    runTest("(1 + 2) * 3", 9);
    runTest("10 / 2 - 3", 2);
    runTest("4.5 + 2.5", 7);
    runTest("10 / (2 + 3)", 2);
    runTest("((3 + 2) * (4 - 1))", 15);
    runTest("3 + 4 * 2 / (1 - 5)", 1); // 3 + (8 / -4) = 3 - 2 = 1
    return 0;
}
