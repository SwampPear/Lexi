#pragma once

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>

namespace Lexi {

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
const std::map<TOKEN_TYPE, std::string> tokenExpressions {
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
const std::map<TOKEN_TYPE, std::string> tokenNames {
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

template <typename T>
struct LLNode {
    std::shared_ptr<T> data;
    std::shared_ptr<LLNode<T>> next;
    std::shared_ptr<LLNode<T>> prev;
};

struct TokenData {
    TOKEN_TYPE tokenType;
    std::string *src;
    int start;
    int end;
};

std::shared_ptr<LLNode<TokenData>> createNode(TOKEN_TYPE tokenType, std::string *src, int start, int end) {
    std::shared_ptr<LLNode<TokenData>> node = std::make_shared<LLNode<TokenData>>();

    std::shared_ptr<TokenData> tokenData = std::make_shared<TokenData>();
    tokenData->tokenType = tokenType;
    tokenData->src = src;
    tokenData->start = start;
    tokenData->end = end;

    node->data = tokenData;

    return node;
}


template <typename T>
void replace(std::shared_ptr<LLNode<T>> replaced, std::shared_ptr<LLNode<T>> replacement) {
    if (replaced == nullptr) {
        throw std::runtime_error("The replaced node cannot be null.");
    }

    if (replacement == nullptr) {
        throw std::runtime_error("The replacement node cannot be null.");
    }

    // record old state
    std::shared_ptr<LLNode<T>> oldNext = replaced->next;

    // replace previous
    replacement->prev = replaced->prev;

    // replace next
    std::shared_ptr<LLNode<T>> currNode = replacement;

    while (currNode->next != nullptr) {
        currNode = currNode->next;
    }

    currNode->next = oldNext;

    if (oldNext != nullptr) {
        oldNext->prev = currNode;
    }

    // connect to replacement
    *replaced = *replacement;
}

std::string tokenNodeToString(std::shared_ptr<LLNode<TokenData>> node, bool displayContent) {
    if (node == nullptr) return "<null>";

    std::stringstream ss;

    ss << "<" << tokenNames.at(node->data->tokenType) << " ";
    ss << node->data->start << " " << node->data->end << "> - ";

    if (node->prev != nullptr) {
        ss << "<" << tokenNames.at(node->prev->data->tokenType) << " ";
        ss << node->prev->data->start << ", " << node->prev->data->end << ">, ";
    } else {
        ss << "<null>, ";
    }

    if (node->next != nullptr) {
        ss << "<" << tokenNames.at(node->next->data->tokenType) << " ";
        ss << node->next->data->start << ", " << node->next->data->end << ">, ";
    } else {
        ss << "<null>, ";
    }

    if (displayContent) {
        std::string display = *node->data->src;
        int i = node->data->start;
        int j = node->data->end - node->data->start;
        ss << display.substr(i, j) << "\n";
    }

    return ss.str();
}

std::string tokenToString(std::shared_ptr<LLNode<TokenData>> node, bool displayContent) {
    std::stringstream ss;

    std::shared_ptr<LLNode<TokenData>> curr = node;

    while (curr != nullptr) {
        ss << tokenNodeToString(curr, displayContent);
        curr = curr->next;
    }

    return ss.str();
}

void tokenizeContentNode(std::shared_ptr<LLNode<TokenData>> node, TOKEN_TYPE tokenType) {
    // regex mapped to token type
    std::string expression = tokenExpressions.at(tokenType);

    int oldEnd = node->data->end;               // length of src
    std::string *src = node->data->src;         // should be copied to all nodes

    // src file content for within content node scope
    std::string input = *src;
    int i = node->data->start;
    int j = node->data->end - node->data->start;
    input = input.substr(i, j);

    // match expression
    std::regex regex(expression);
    std::smatch match;
    auto begin = std::sregex_iterator(input.begin(), input.end(), regex);
    auto end = std::sregex_iterator();

    // current index of search
    int offset = node->data->start;
    int currIndex = 0;
    int matchStart = 0;
    int matchEnd = 0;
    bool matchFound = false;

    std::shared_ptr<LLNode<TokenData>> rootNode = nullptr;
    std::shared_ptr<LLNode<TokenData>> currNode = nullptr;

    for (auto it = begin; it != end; ++it) {
        // match information
        matchFound = true;
        match = *it;
        std::string matchContents = match.str(0);
        matchStart = match.position(0);
        matchEnd = matchStart + match.length(0);

        // prefix content node
        if (currIndex != matchStart) {
            std::shared_ptr<LLNode<TokenData>> node = createNode(
                TOKEN_TYPE::CONTENT, src, currIndex + offset, matchStart + offset);

            node->next = nullptr;
            node->prev = nullptr;

            // update index
            currIndex = matchStart;

            // link node
            if (rootNode == nullptr) {      // first node case
                rootNode = node;
                currNode = rootNode;
            } else {                        // not first
                node->prev = currNode;
                node->prev->next = node;

                currNode = node;
            }
        }

        // lexical node
        std::shared_ptr<LLNode<TokenData>> node = createNode(
            tokenType, src, matchStart + offset, matchEnd + offset);
        node->next = nullptr;
        node->prev = nullptr;

        // update index
        currIndex = matchEnd;

        // link node
        if (rootNode == nullptr) {      // first node case
            rootNode = node;
            currNode = rootNode;
        } else {                        // not first
            node->prev = currNode;
            node->prev->next = node;

            currNode = node;
        }
    }

    // suffix content node
    if (currIndex + offset != oldEnd && matchFound) {
        std::shared_ptr<LLNode<TokenData>> node = createNode(
            TOKEN_TYPE::CONTENT, src, currIndex + offset, oldEnd);

        node->next = nullptr;
        node->prev = nullptr;

        // link node
        if (rootNode == nullptr) {      // first node case
            rootNode = node;
            currNode = rootNode;
        } else {                        // not first
            node->prev = currNode;
            node->prev->next = node;

            currNode = node;
        }
    }

    // insert new node tree in place of old
    if (rootNode != nullptr) {
        replace(node, rootNode);
    }
}

void tokenizeNode(std::shared_ptr<LLNode<TokenData>> node, TOKEN_TYPE tokenType) {
    std::shared_ptr<LLNode<TokenData>> currNode = node;

    while (currNode != nullptr) {
        if (currNode->data->tokenType == TOKEN_TYPE::CONTENT) {
            tokenizeContentNode(currNode, tokenType);
        }

        currNode = currNode->next;
    }
}

std::shared_ptr<LLNode<TokenData>> tokenize(std::string *src) {
    std::shared_ptr<LLNode<TokenData>> root = createNode(
        TOKEN_TYPE::CONTENT, src, 0, src->length());
    root->next = nullptr;
    root->prev = nullptr;

    tokenizeNode(root, TOKEN_TYPE::STRING);
    tokenizeNode(root, TOKEN_TYPE::L_DELIMETER);
    tokenizeNode(root, TOKEN_TYPE::R_DELIMETER);
    tokenizeNode(root, TOKEN_TYPE::L_CURLY_DELIMETER);
    tokenizeNode(root, TOKEN_TYPE::R_CURLY_DELIMETER);
    std::cout << tokenToString(root, true) << std::endl;

    return root;
}

}  // namespace Lexi