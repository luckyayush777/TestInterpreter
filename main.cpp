#include<iostream>
#include<string>

#include"token.h"
#include"lexer.h"
#include"parser.h"
#include"expr.h"
#include"stmt.h"

int main() {


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

    for (const Token& t : tokens) {
        std::cout << "Token: " << t.lexeme << " Type: ";
        switch (t.type) {
            case TokenType::NUMBER: std::cout << "NUMBER (" << t.numberValue << ")"; break;
            case TokenType::PLUS: std::cout << "PLUS"; break;
            case TokenType::MINUS: std::cout << "MINUS"; break;
            case TokenType::STAR: std::cout << "STAR"; break;
            case TokenType::SLASH: std::cout << "SLASH"; break;
            case TokenType::LEFT_PAREN: std::cout << "LEFT_PAREN"; break;
            case TokenType::RIGHT_PAREN: std::cout << "RIGHT_PAREN"; break;
            case TokenType::LEFT_BRACE: std::cout << "LEFT_BRACE"; break;
            case TokenType::RIGHT_BRACE: std::cout << "RIGHT_BRACE"; break;
            case TokenType::END_OF_FILE: std::cout << "EOF"; break;
            case TokenType::INVALID: std::cout << "INVALID"; break;
            case TokenType::SEMICOLON: std::cout << "SEMICOLON"; break;
            default: std::cout << "UNKNOWN"; break;
        }
        std::cout << '\n';
    }
    Parser parser(tokens); 
    std::unique_ptr<Stmt> stmt = parser.parseStatement();
    stmt->execute(); // Evaluate the expression
    }
}
