#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "expr.h"
#include "stmt.h"
#include "environment.h"
#include "util.h"

// A central function to run the interpreter on a string of source code
void run(const std::string& source, std::shared_ptr<Environment> env) {
    try {
        Lexer lexer(source);
        auto tokens = lexer.tokenize();
        
        // Optional: You can uncomment this to see the tokens for debugging file scripts
        //std::cout<< "Tokens:\n";
        //ShowTokens(tokens);

        Parser parser(tokens);
        auto statements = parser.parse();

        for (const auto& stmt : statements) {
            if (stmt) {
                stmt->execute(env);
            }
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
    }
}

// Reads an entire file into a string
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << path << "'." << std::endl;
        exit(74); // Standard exit code for I/O errors
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Runs the interpreter on a script file
void runFile(const std::string& path, std::shared_ptr<Environment> env) {
    std::string source = readFile(path);
    run(source, env);
}

// Runs the interactive REPL
void runPrompt(std::shared_ptr<Environment> env) {
    std::string line;
    while (true) {
        std::cout << ">> ";
        if (!std::getline(std::cin, line) || line.empty()) {
            break;
        }
        run(line, env);
    }
}

int main(int argc, char* argv[]) {
    auto globalEnv = std::make_shared<Environment>();

    if (argc > 2) {
        std::cout << "Usage: TestInterpreter [script]" << std::endl;
        return 64; // Standard exit code for command-line usage error
    } else if (argc == 2) {
        // Run from a file
        runFile(argv[1], globalEnv);
    } else {
        // Run the interactive prompt
        runPrompt(globalEnv);
    }

    return 0;
}
