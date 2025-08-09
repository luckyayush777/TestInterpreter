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

        while(!isAtEnd() && (isdigit(peek()) || peek() == '.'))
        {
            lexeme += advance();
        }
        return Token(TokenType::NUMBER, lexeme, std::stod(lexeme));
    }

    Token identifier(char firstChar);
};







