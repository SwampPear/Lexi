// Copyright 2024 Michael Vaden

#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <fstream>
#include <memory>
#include "utils.hpp"
#include "tokenizer.hpp"

int main() {
    std::filesystem::path cwd = getCWD();
    std::string src = "main.blam";

    std::string srcContents = readFile(cwd/src);
    std::shared_ptr<LLNode<TokenData>> root = tokenize(&srcContents);

    return EXIT_SUCCESS;
}
