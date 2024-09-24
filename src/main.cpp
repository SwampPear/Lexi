// Copyright 2024 Michael Vaden

#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include "src/utils.hpp"
#include "src/tokenizer.hpp"

int main() {
    std::filesystem::path cwd = getCWD();
    std::string src = "main.blam";

    std::string srcContents = readFile(cwd/src);
    LLNode<TokenData> *root = tokenize(&srcContents);

    return EXIT_SUCCESS;
}
