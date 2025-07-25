#pragma once
#include <string>
#include <vector>

#include"token.h"


class Lexer{
    const std::string source;
    size_t current = 0;


    public : Lexer(const std::string& source) : source(source) {}

    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;

        while(!isAtEnd())
        {
            char c = advance();

            switch(c)
            {
                case '+':
                    tokens.emplace_back(TokenType::PLUS, "+");
                    break;
                case '-':
                    tokens.emplace_back(TokenType::MINUS, "-");
                    break;
                case '*':
                    tokens.emplace_back(TokenType::STAR, "*");
                    break;
                case '/':
                    tokens.emplace_back(TokenType::SLASH, "/");
                    break;
                case '(':
                    tokens.emplace_back(TokenType::LEFT_PAREN, "(");
                    break;
                case ')':
                    tokens.emplace_back(TokenType::RIGHT_PAREN, ")");
                    break;
                default:
                    if(isdigit(c) || (c == '.'))
                    {
                       tokens.push_back(number(c));
                    }
                    else
                    {
                        tokens.emplace_back(TokenType::INVALID, std::string(1, c));
                    }
                
            }
        }
        tokens.emplace_back(TokenType::END_OF_FILE, ""); // End of input token
        return tokens;
    }

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
};







