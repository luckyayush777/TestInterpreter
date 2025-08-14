#pragma once
#include <string>
#include <vector>

#include"token.h"


class Lexer{
    const std::string source;
    size_t current = 0;


    public : Lexer(const std::string& source) : source(source) {}

    std::vector<Token> tokenize();

    const char advance()
    {
        if(isAtEnd()) return '\0';
        return source[current++];
    }

    bool isAtEnd() const
    {
        return current >= source.size();
    }

    char peek() const{
        return isAtEnd() ? '\0' : source[current];
    }

    Token number(char firstChar)
{
    std::string lexeme(1, firstChar);

    // Handle digits before decimal point
    while(!isAtEnd() && isdigit(peek()))
    {
        lexeme += advance();
    }
    
    // Handle decimal point and digits after (only one decimal point allowed)
    if (!isAtEnd() && peek() == '.') {
        // Look ahead to make sure there's a digit after the decimal
        if (current + 1 < source.size() && isdigit(source[current + 1])) {
            lexeme += advance(); // consume the '.'
            while(!isAtEnd() && isdigit(peek())) {
                lexeme += advance();
            }
        }
    }
    
    return Token(TokenType::NUMBER, lexeme, std::stod(lexeme));
}

    Token identifier(char firstChar);

    
    bool match(char expected);
};







