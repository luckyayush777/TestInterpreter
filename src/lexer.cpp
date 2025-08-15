

#include<unordered_map>
#include<cctype>

#include"token.h"
#include"lexer.h"

static const std::unordered_map<std::string, TokenType> keywords = {
    {"and",    TokenType::AND},
    {"else",   TokenType::ELSE},
    {"false",  TokenType::FALSE},
    {"for",    TokenType::FOR},
    {"fun",    TokenType::FUNCTION},
    {"if",     TokenType::IF},
    {"nil",    TokenType::NIL},
    {"or",     TokenType::OR},
    {"return", TokenType::RETURN},
    {"true",   TokenType::TRUE},
    {"var",    TokenType::VAR},
    {"while",  TokenType::WHILE},
    {"print", TokenType::PRINT},
};

Token Lexer::identifier(char firstChar)
{
    std::string lexeme(1, firstChar);

    while (!isAtEnd() && (isalnum(peek()) || peek() == '_')) {
        lexeme += advance();
    }
    // Check if the lexeme is a keyword
    auto it = keywords.find(lexeme);
    if (it != keywords.end()) {
        return Token(it->second, lexeme);
    }
    return Token(TokenType::IDENTIFIER, lexeme);
}


std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        char c = advance();

        switch (c) {
            case ' ':
            case '\t':
            case '\n':
                // Ignore whitespace
                break;
            case ',' : 
                tokens.emplace_back(TokenType::COMMA, ",");
                break;
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
            case '{':
                tokens.emplace_back(TokenType::LEFT_BRACE, "{");
                break;
            case '}':
                tokens.emplace_back(TokenType::RIGHT_BRACE, "}");
                break;
            // Inside the switch (c) { ... }
            case '>':
                if(match('=')) {
                    tokens.emplace_back(TokenType::GREATER_THAN_EQUALS, ">=");
                } else {
                    tokens.emplace_back(TokenType::GREATER_THAN, ">");
                }
                break;
            case '<':
                if(match('=')) {
                    tokens.emplace_back(TokenType::LESS_THAN_EQUALS, "<=");
                } else {
                    tokens.emplace_back(TokenType::LESS_THAN, "<"); 
                }
                break;
            case '=':
                if (match('=')) {
                    tokens.emplace_back(TokenType::EQUALS_EQUALS, "==");
                } else {
                    tokens.emplace_back(TokenType::EQUALS, "=");
                }
                break;
            case '!':
                if (match('=')) {
                    tokens.emplace_back(TokenType::BANG_EQUALS, "!=");
                } else {
                    tokens.emplace_back(TokenType::BANG, "!");  
                }
                break;
            case ';':
                tokens.emplace_back(TokenType::SEMICOLON, ";");
                break;
            default:
                if (isdigit(c) || (c == '.')) {
                    tokens.push_back(number(c));
                } else if (isalpha(c) || c == '_') {
                    tokens.push_back(identifier(c));
                }
                else {
                    tokens.emplace_back(TokenType::INVALID, std::string(1, c));
                }
        }
    }
    tokens.emplace_back(TokenType::END_OF_FILE, ""); // End of input token
    return tokens;
}

bool Lexer::match(char expected) {
    if (isAtEnd() || source[current] != expected) {
        return false;
    }
    current++;
    return true;
}
