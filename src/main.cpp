#include<iostream>
#include<string>

#include"token.h"
#include"lexer.h"
#include"parser.h"
#include"expr.h"
#include"stmt.h"

int main() {

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
            case TokenType::IDENTIFIER: std::cout << "IDENTIFIER (" << t.lexeme << ")"; break;
            case TokenType::VAR: std::cout << "VAR"; break;
            case TokenType::IF: std::cout << "IF"; break;
            case TokenType::ELSE: std::cout << "ELSE"; break;
            case TokenType::WHILE: std::cout << "WHILE"; break;
            case TokenType::FOR: std::cout << "FOR"; break;
            case TokenType::FUNCTION: std::cout << "FUNCTION"; break;
            case TokenType::PRINT: std::cout << "PRINT"; break;
            case TokenType::EQUALS: std::cout << "EQUALS"; break;
            case TokenType::EQUALS_EQUALS: std::cout << "EQUALS_EQUALS"; break;
            case TokenType::TRUE: std::cout << "TRUE"; break;
            case TokenType::FALSE: std::cout << "FALSE"; break;
            case TokenType::NIL: std::cout << "NIL"; break;
            case TokenType::AND: std::cout << "AND"; break;
            case TokenType::OR: std::cout << "OR"; break;
            case TokenType::STRING: std::cout << "STRING"; break;
            default: std::cout << "UNKNOWN"; break;
        }
        std::cout << '\n';
    }
    Parser parser(tokens); 
    std::unique_ptr<Stmt> stmt = parser.parseStatement();
    stmt->execute(); // Evaluate the expression
    }
}
