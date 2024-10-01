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
    std::string path = getCWD()/"main.blam";
    std::string src = readFile(path);

    Lexi::Tokenizer tokenizer = Lexi::Tokenizer();
    tokenizer.addRule("STRING", "\"[a-zA-Z0-9\\s\\}]*\"");
    tokenizer.addRule("SINGLE_LINE_COMMENT", "\\/\\/[\\sa-zA-Z0-9]*\n*");
    tokenizer.addRule("MULTI_LINE_COMMENT", "\\/\\*[\\sa-zA-Z0-9]*\\*\\/");
    tokenizer.addRule("L_DELIMETER", "\\(");
    tokenizer.addRule("R_DELIMETER", "\\)");
    tokenizer.addRule("L_CURLY_DELIMETER", "\\{");
    tokenizer.addRule("R_CURLY_DELIMETER", "\\}");
    tokenizer.addRule("L_SQUARE_DELIMETER", "\\[");
    tokenizer.addRule("R_SQUARE_DELIMETER", "\\]");
    tokenizer.addRule("OP_DOT", "\\.");
    tokenizer.addRule("OP_PLUS", "\\+");
    tokenizer.addRule("OP_MINUS", "\\-");
    tokenizer.addRule("OP_EQUALS", "=");
    tokenizer.addRule("OP_SLASH", "/");
    tokenizer.addRule("KEYWORD", "return");
    tokenizer.addRule("SPACE", "\\s+");
    
    std::shared_ptr<Lexi::LLNode> root = tokenizer.tokenize(&src);

    return EXIT_SUCCESS;
}
