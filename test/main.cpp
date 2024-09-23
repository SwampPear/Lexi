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
    TokenNode *prevNode = node;
    TokenNode *currNode = node;

    // test each node
    // node 1
    assert(currNode->tokenType == TOKEN_TYPE::CONTENT);
    assert(currNode->prev == nullptr);
    assert(currNode->start == 0);
    assert(currNode->end == 54);

    // node 1 next
    assert(currNode->next->tokenType == TOKEN_TYPE::L_DELIMETER);
    assert(currNode->next->start == 54);
    assert(currNode->next->end == 55);

    // node 2
    currNode = currNode->next;
    assert(currNode->tokenType == TOKEN_TYPE::L_DELIMETER);
    assert(currNode->prev == prevNode);
    assert(currNode->start == 54);
    assert(currNode->end == 55);

    // node 2 next
    assert(currNode->next->tokenType == TOKEN_TYPE::R_DELIMETER);
    assert(currNode->next->start == 55);
    assert(currNode->next->end == 56);

    // node 2 prev
    assert(prevNode->tokenType == TOKEN_TYPE::CONTENT);
    assert(prevNode->start == 0);
    assert(prevNode->end == 54);

    // node 3
    prevNode = prevNode->next;
    currNode = currNode->next;
    assert(currNode->tokenType == TOKEN_TYPE::R_DELIMETER);
    assert(currNode->prev == prevNode);
    assert(currNode->start == 55);
    assert(currNode->end == 56);

    // node 3 next
    assert(currNode->next->tokenType == TOKEN_TYPE::CONTENT);
    assert(currNode->next->start == 56);
    assert(currNode->next->end == 57);

    // node 3 prev
    assert(prevNode->tokenType == TOKEN_TYPE::L_DELIMETER);
    assert(prevNode->start == 54);
    assert(prevNode->end == 55);

    // node 4
    prevNode = prevNode->next;
    currNode = currNode->next;
    assert(currNode->tokenType == TOKEN_TYPE::CONTENT);
    assert(currNode->prev == prevNode);
    assert(currNode->start == 56);
    assert(currNode->end == 57);

    // node 4 next
    assert(currNode->next->tokenType == TOKEN_TYPE::L_CURLY_DELIMETER);
    assert(currNode->next->start == 57);
    assert(currNode->next->end == 58);

    // node 4 prev
    assert(prevNode->tokenType == TOKEN_TYPE::R_DELIMETER);
    assert(prevNode->start == 55);
    assert(prevNode->end == 56);

    // node 5
    prevNode = prevNode->next;
    currNode = currNode->next;
    assert(currNode->tokenType == TOKEN_TYPE::L_CURLY_DELIMETER);
    assert(currNode->prev == prevNode);
    assert(currNode->start == 57);
    assert(currNode->end == 58);

    // node 5 next
    assert(currNode->next->tokenType == TOKEN_TYPE::CONTENT);
    assert(currNode->next->start == 58);
    assert(currNode->next->end == 71);

    // node 5 prev
    assert(prevNode->tokenType == TOKEN_TYPE::CONTENT);
    assert(prevNode->start == 56);
    assert(prevNode->end == 57);

    // node 6
    prevNode = prevNode->next;
    currNode = currNode->next;
    assert(currNode->tokenType == TOKEN_TYPE::CONTENT);
    assert(currNode->prev == prevNode);
    assert(currNode->start == 58);
    assert(currNode->end == 71);

    // node 6 next
    assert(currNode->next->tokenType == TOKEN_TYPE::STRING);
    assert(currNode->next->start == 71);
    assert(currNode->next->end == 93);

    // node 6 prev
    assert(prevNode->tokenType == TOKEN_TYPE::L_CURLY_DELIMETER);
    assert(prevNode->start == 57);
    assert(prevNode->end == 58);

    // node 7
    prevNode = prevNode->next;
    currNode = currNode->next;
    assert(currNode->tokenType == TOKEN_TYPE::STRING);
    assert(currNode->prev == prevNode);
    assert(currNode->start == 71);
    assert(currNode->end == 93);

    // node 7 next
    assert(currNode->next->tokenType == TOKEN_TYPE::CONTENT);
    assert(currNode->next->start == 93);
    assert(currNode->next->end == 94);

    // node 7 prev
    assert(prevNode->tokenType == TOKEN_TYPE::CONTENT);
    assert(prevNode->start == 58);
    assert(prevNode->end == 71);

    // node 8
    prevNode = prevNode->next;
    currNode = currNode->next;
    assert(currNode->tokenType == TOKEN_TYPE::CONTENT);
    assert(currNode->prev == prevNode);
    assert(currNode->start == 93);
    assert(currNode->end == 94);

    // node 8 next
    assert(currNode->next->tokenType == TOKEN_TYPE::R_CURLY_DELIMETER);
    assert(currNode->next->start == 94);
    assert(currNode->next->end == 95);

    // node 8 prev
    assert(prevNode->tokenType == TOKEN_TYPE::STRING);
    assert(prevNode->start == 71);
    assert(prevNode->end == 93);

    // node 9
    prevNode = prevNode->next;
    currNode = currNode->next;
    assert(currNode->tokenType == TOKEN_TYPE::R_CURLY_DELIMETER);
    assert(currNode->prev == prevNode);
    assert(currNode->start == 94);
    assert(currNode->end == 95);

    // node 9 next
    assert(currNode->next == nullptr);
    //assert(currNode->next->tokenType == TOKEN_TYPE::R_CURLY_DELIMETER);
    //assert(currNode->next->start == 94);
    //assert(currNode->next->end == 95);

    // node 9 prev
    assert(prevNode->tokenType == TOKEN_TYPE::CONTENT);
    assert(prevNode->start == 93);
    assert(prevNode->end == 94);


    std::cout << "All tests passed" << std::endl;
}

int main() {
    test_basic();

    return EXIT_SUCCESS;
}