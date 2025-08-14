#include<iostream>
#include<string>

#include"token.h"
#include"lexer.h"
#include"parser.h"
#include"expr.h"
#include"stmt.h"
#include"environment.h"
#include"util.h"

int main() {

    auto globalEnv = std::make_shared<Environment>();
    //comment out the test cases in src/tests.cpp
    std::string line;
    while(true)
    {
        std::cout<<">>";
        if(!std::getline(std::cin, line) || line.empty()) {
            break; // Exit on empty input
        }
    //std::string input = "3+4.5*2-1";
    Lexer lexer(line);
    auto tokens = lexer.tokenize();
    if(tokens.empty()) {
        std::cout << "No tokens generated.\n";
        continue; // Skip to the next input
    }
    ShowTokens(tokens); // Display the tokens for debugging
    
    Parser parser(tokens); 
    std::unique_ptr<Stmt> stmt = parser.parseStatement();
    if(stmt){
        stmt->execute(globalEnv); // Execute the statement in the global environment
    }

    }
}
