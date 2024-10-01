// Copyright 2024 Michael Vaden

#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <fstream>
#include <memory>
#include "utils.hpp"
#include "lexi.hpp"

int main() {
    std::filesystem::path cwd = getCWD();
    std::string src = "main.blam";

    /*
    // lexeme types of token
    enum TOKEN_TYPE {
        STRING,
        CONTENT,
        SINGLE_LINE_COMMENT,
        MULTI_LINE_COMMENT,
        L_DELIMETER,
        R_DELIMETER,
        L_CURLY_DELIMETER,
        R_CURLY_DELIMETER,
        L_SQUARE_DELIMETER,
        R_SQUARE_DELIMETER,
        OP_DOT,
        OP_PLUS,
        OP_MINUS,
        OP_EQUALS,
        OP_SLASH,
        SPACE,
        KEYWORD
    };

    // maps pertinent token type to corresponding regular expression
    const std::map<int, std::string> tokenExpressions {
        {TOKEN_TYPE::STRING, "\"[a-zA-Z0-9\\s\\}]*\""},
        {TOKEN_TYPE::SINGLE_LINE_COMMENT, "\\/\\/[\\sa-zA-Z0-9]*\n*"},
        {TOKEN_TYPE::MULTI_LINE_COMMENT, "\\/\\*[\\sa-zA-Z0-9]*\\*\\/"},
        {TOKEN_TYPE::L_DELIMETER, "\\("},
        {TOKEN_TYPE::R_DELIMETER, "\\)"},
        {TOKEN_TYPE::L_CURLY_DELIMETER, "\\{"},
        {TOKEN_TYPE::R_CURLY_DELIMETER, "\\}"},
        {TOKEN_TYPE::L_SQUARE_DELIMETER, "\\["},
        {TOKEN_TYPE::R_SQUARE_DELIMETER, "\\]"},
        {TOKEN_TYPE::OP_DOT, "\\."},
        {TOKEN_TYPE::OP_PLUS, "\\+"},
        {TOKEN_TYPE::OP_MINUS, "-"},
        {TOKEN_TYPE::OP_EQUALS, "="},
        {TOKEN_TYPE::OP_SLASH, "/"},
        {TOKEN_TYPE::SPACE, "\\s*"},
        {TOKEN_TYPE::KEYWORD, "return"}
    };

    // maps token type to corresponding token name
    const std::map<int, std::string> tokenNames {
        {TOKEN_TYPE::CONTENT, "CONTENT"},
        {TOKEN_TYPE::STRING, "STRING"},
        {TOKEN_TYPE::SINGLE_LINE_COMMENT, "SINGLE_LINE_COMMENT"},
        {TOKEN_TYPE::MULTI_LINE_COMMENT, "MULTI_LINE_COMMENT"},
        {TOKEN_TYPE::L_DELIMETER, "L_DELIMETER"},
        {TOKEN_TYPE::R_DELIMETER, "R_DELIMETER"},
        {TOKEN_TYPE::L_CURLY_DELIMETER, "L_CURLY_DELIMETER"},
        {TOKEN_TYPE::R_CURLY_DELIMETER, "R_CURLY_DELIMETER"},
        {TOKEN_TYPE::L_SQUARE_DELIMETER, "L_SQUARE_DELIMETER"},
        {TOKEN_TYPE::R_SQUARE_DELIMETER, "L_SQUARE_DELIMETER"},
        {TOKEN_TYPE::OP_DOT, "OP_DOT"},
        {TOKEN_TYPE::OP_PLUS, "OP_PLUS"},
        {TOKEN_TYPE::OP_MINUS, "OP_MINUS"},
        {TOKEN_TYPE::OP_EQUALS, "OP_EQUALS"},
        {TOKEN_TYPE::OP_SLASH, "OP_SLASH"},
        {TOKEN_TYPE::SPACE, "SPACE"},
        {TOKEN_TYPE::KEYWORD, "KEYWORD"}
    };

    Lexi::Tokenizer tokenizer = Lexi::Tokenizer();
    tokenizer.addRule("STRING", "\"[a-zA-Z0-9\\s\\}]*\"");
    */

    std::string srcContents = readFile(cwd/src);
    std::shared_ptr<Lexi::LLNode> root = Lexi::tokenize(&srcContents);

    return EXIT_SUCCESS;
}
