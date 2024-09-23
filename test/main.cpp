#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include "utils.hpp"
#include "tokenizer.hpp"

void test_basic() {
    // load contents of file
    std::filesystem::path cwd = getCWD();
    std::string src = "main.blam";
    std::string srcContents = readFile(cwd/src);

    // setup node
    TokenNode *node = tokenize(&srcContents);

    // test each node

    std::cout << tokenNodeToString(node, true) << std::endl;
}

int main() {
    test_basic();

    return EXIT_SUCCESS;
}