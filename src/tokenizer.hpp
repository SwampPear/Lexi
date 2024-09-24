#include <map>
#include <regex>
#include <sstream>
#include "linked_list.hpp"

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

struct TokenData {
    TOKEN_TYPE tokenType;
    std::string *src;
    int start;
    int end;
};

//void tokenizeContentNode(LLNode<TokenData> *node, TOKEN_TYPE tokenType) {
    /*
    if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "a\n"; };
    std::string lexeme = tokenExpressions.at(tokenType);

    // old state
    TokenNode *oldPrev = node->prev;
    TokenNode *oldNext = node->next;
    TokenNode *newRoot = nullptr;
    TokenNode *currNode = node;

    int oldEnd = node->end;
    std::string *src = node->src;           // will be copied to all nodes

    // src file content for within content node scope
    std::string input = *src;
    input = input.substr(node->start, node->end - node->start);

    // match lexeme
    std::regex regex(lexeme);
    std::smatch match;
    auto begin = std::sregex_iterator(input.begin(), input.end(), regex);
    auto end = std::sregex_iterator();

    // current index of search
    int offset = node->start;
    int currIndex = 0;
    int matchStart = 0;
    int matchEnd = 0;
    bool matchFound = false;

    for (auto it = begin; it != end; ++it) {
        if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "b\n"; };
        // match info
        matchFound = true;
        match = *it;
        std::string matchContents = match.str(0);
        matchStart = match.position(0);
        matchEnd = matchStart + match.length(0);

        if (currIndex != matchStart) {
            if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "c\n"; };
            TokenNode *newNode = new TokenNode;
            newNode->tokenType = TOKEN_TYPE::CONTENT;
            newNode->src = src;
            newNode->start = currIndex + offset;
            newNode->end = matchStart + offset;

            // update index
            currIndex = matchStart;

            // update positions
            if (newRoot == nullptr) {
                if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "d\n"; };
                newRoot = newNode;
                newRoot->prev = oldPrev;
            } else {
                newNode->prev = currNode;
                currNode->next = newNode;
            }

            currNode = newNode;
        }

        // lexical node
        TokenNode *newNode = new TokenNode;
        newNode->tokenType = tokenType;
        newNode->src = src;
        newNode->start = matchStart + offset;
        newNode->end = matchEnd + offset;

        // update index
        currIndex = matchEnd;

        // update position
        if (newRoot == nullptr) {
            if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "e\n"; };
            newRoot = newNode;
            newRoot->prev = oldPrev;
        } else {
            if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "e2\n"; };
            newNode->prev = currNode;
            currNode->next = newNode;
        }

        currNode = newNode;
    }

    if (currIndex + offset != oldEnd && matchFound) {
        if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "f\n"; };
        // create and insert post content node
        TokenNode *newNode = new TokenNode;
        newNode->tokenType = TOKEN_TYPE::CONTENT;
        newNode->src = src;
        newNode->start = currIndex + offset;
        newNode->end = oldEnd;

        // update position
        if (newRoot == nullptr) {
            if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "f2\n"; };
            newRoot = newNode;
            newRoot->prev = oldPrev;
        } else {
            if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "f3\n"; };
            //if (oldPrev->prev != nullptr) {
            //    oldPrev
            //}
            currNode->next = newNode;
            newNode->prev = currNode;
        }

        currNode = newNode;
    }


    if (oldPrev != nullptr) {
        if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "g\n"; };
        if (currNode == node) {
            if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "g2\n"; };
            newRoot = node;
        }
        std::cout << tokenNames.at(oldPrev->tokenType) << std::endl;
        std::cout << tokenNames.at(newRoot->tokenType) << std::endl;
        std::cout << tokenNames.at(currNode->tokenType) << std::endl;
        //std::cout << matchEnd << std::endl;
        oldPrev->next = newRoot;
    } else {
        if (newRoot != nullptr) {
            *node = *newRoot;
        }
    }

    if (oldNext != nullptr) {
        if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "h\n"; };
        oldNext->prev = currNode;
        currNode->next = oldNext;
    }
    */
//}

/*
void tokenizeNode(TokenNode *node, TOKEN_TYPE tokenType) {
    TokenNode *currNode = node;

    while (currNode != nullptr) {
        if (currNode->tokenType == TOKEN_TYPE::CONTENT) {
            tokenizeContentNode(currNode, tokenType);
            std::cout << tokenNodeToString(node, true) << std::endl << std::endl << std::endl;
        }

        currNode = currNode->next;
    }
}*/

std::string tokenNodeToString(LLNode<TokenData> *node, bool displayContent) {
    std::stringstream ss;

    if (node != nullptr) {
        ss << "<" << tokenNames.at(node->data->tokenType);
        ss << " " << node->data->start << " ";
        ss << node->data->end;
        ss << ">";

        ss << " - ";

        if (node->prev != nullptr) {
            ss << "<" << tokenNames.at(node->prev->data->tokenType);
            ss << " " << node->prev->data->start << ", ";
            ss << " " << node->prev->data->end << ">, ";
        } else {
            ss << "<null>, ";
        }

        if (node->next != nullptr) {
            ss << "<" << tokenNames.at(node->next->data->tokenType);
            ss << " " << node->next->data->start << ", ";
            ss << " " << node->next->data->end << ">\n";
        } else {
            ss << "<null>\n";
        }

        if (displayContent) {
            std::string display = *node->data->src;
            int i = node->data->start;
            int j = node->data->end - node->data->start;
            ss << display.substr(i, j) << "\n";
        }
    } else {
        ss << "null" << std::endl;
    }

    return ss.str();
}

std::string tokenToString(LLNode<TokenData> *node, bool displayContent) {
    std::stringstream ss;

    LLNode<TokenData> *curr = node;

    while(curr != nullptr) {
        std::cout << "it" << std::endl;
        ss << tokenNodeToString(curr, displayContent);
        curr = curr->next;
    }

    return ss.str();
}

void tokenizeContentNode(LLNode<TokenData> *node, TOKEN_TYPE tokenType) {
    if (node == nullptr) return;
    if (node->data->tokenType != TOKEN_TYPE::CONTENT) return;

    std::string lexeme = tokenExpressions.at(tokenType);
    std::cout << "b" << std::endl;

    int oldEnd = node->data->end;
    std::string *src = node->data->src;           // will be copied to all nodes

    // src file content for within content node scope
    std::string input = *src;
    input = input.substr(node->data->start, node->data->end - node->data->start);

    // match lexeme
    std::regex regex(lexeme);
    std::smatch match;
    auto begin = std::sregex_iterator(input.begin(), input.end(), regex);
    auto end = std::sregex_iterator();

    // current index of search
    int offset = node->data->start;
    int currIndex = 0;
    int matchStart = 0;
    int matchEnd = 0;
    bool matchFound = false;

    LLNode<TokenData> *rootNode;
    LLNode<TokenData> *currNode;
    std::cout << "c" << std::endl;

    for (auto it = begin; it != end; ++it) {
        std::cout << "d" << std::endl;
        // match info
        matchFound = true;
        match = *it;
        std::string matchContents = match.str(0);
        matchStart = match.position(0);
        matchEnd = matchStart + match.length(0);

        if (currIndex != matchStart) {
            std::cout << "e" << std::endl;
            LLNode<TokenData> *node = new LLNode<TokenData>();
            TokenData *tokenData = new TokenData;
            tokenData->tokenType = TOKEN_TYPE::CONTENT;
            tokenData->src = src;
            tokenData->start = currIndex + offset;
            tokenData->end = matchStart + offset;

            node->data = tokenData;
            node->next = nullptr;
            node->prev = nullptr;

            // update index
            currIndex = matchStart;

            // link node
            if (rootNode == nullptr) {      // first node case
                // initially set iterator node
                rootNode = node;
                currNode = rootNode;
            } else {                        // not first
                // link this node to iterator node
                node->prev = currNode;
                node->prev->next = node;

                // iterate iterator node
                currNode = node;
            }
        }

        // lexical node
        LLNode<TokenData> *node = new LLNode<TokenData>();
        TokenData *tokenData = new TokenData;
        tokenData->tokenType = tokenType;
        tokenData->src = src;
        tokenData->start = matchStart + offset;
        tokenData->end = matchEnd + offset;

        node->data = tokenData;
        node->next = nullptr;
        node->prev = nullptr;

        // update index
        currIndex = matchEnd;

        // link node
        if (rootNode == nullptr) {      // first node case
            // initially set iterator node
            rootNode = node;
            currNode = rootNode;
        } else {                        // not first
            // link this node to iterator node
            node->prev = currNode;
            node->prev->next = node;

            // iterate iterator node
            currNode = node;
        }
    }

    // suffix content node
    if (currIndex + offset != oldEnd && matchFound) {
        std::cout << "f" << std::endl;
        if (tokenType == TOKEN_TYPE::R_DELIMETER) { std::cout << "f\n"; };
        // create and insert post content node
        LLNode<TokenData> *node = new LLNode<TokenData>();
        TokenData *tokenData = new TokenData;
        tokenData->tokenType = TOKEN_TYPE::CONTENT;
        tokenData->src = src;
        tokenData->start = currIndex + offset;
        tokenData->end = oldEnd;

        node->data = tokenData;
        node->next = nullptr;
        node->prev = nullptr;

        // link node
        if (rootNode == nullptr) {      // first node case
            std::cout << "g" << std::endl;
            // initially set iterator node
            rootNode = node;
            currNode = rootNode;
        } else {                        // not first
            std::cout << "h" << std::endl;
            // link this node to iterator node
            node->prev = currNode;
            node->prev->next = node;

            // iterate iterator node
            currNode = node;
        }
    }

    if (rootNode != nullptr) {
        replace(node, rootNode);
    }

    std::cout << tokenToString(node, true) << std::endl << std::endl << std::endl << std::endl;
}

void tokenizeNode(LLNode<TokenData> *node, TOKEN_TYPE tokenType) {
    LLNode<TokenData> *currNode = node;

    while (currNode != nullptr) {
        LLNode<TokenData> *nextNode = currNode->next;

        std::cout << "a" << std::endl;
        tokenizeContentNode(currNode, tokenType);
        std::cout << "b" << std::endl;

        currNode = nextNode;
    }
}

LLNode<TokenData> *tokenize(std::string *srcContents) {
    LLNode<TokenData> *root = new LLNode<TokenData>();
    TokenData *tokenData = new TokenData;
    tokenData->tokenType = TOKEN_TYPE::CONTENT;
    tokenData->src = srcContents;
    tokenData->start = 0;
    tokenData->end = srcContents->length();

    root->data = tokenData;
    root->next = nullptr;
    root->prev = nullptr;

    tokenizeContentNode(root, TOKEN_TYPE::STRING);
    //std::cout << tokenNodeToString(root, true) << std::endl;
    //tokenizeContentNode(root->next, TOKEN_TYPE::L_DELIMETER);
    //std::cout << tokenNames.at(root->data->tokenType) << std::endl;

    //tokenizeContentNode(root, TOKEN_TYPE::L_DELIMETER);
    
        
    /*
    // init root content node
    TokenNode *root = new TokenNode;
    root->tokenType = TOKEN_TYPE::CONTENT;
    root->src = srcContents;
    root->start = 0;
    root->end = srcContents->length();
    root->next = nullptr;

    // tokenize for each lexeme
    tokenizeNode(root, TOKEN_TYPE::STRING);
    //std::cout << tokenNodeToString(root, true) << std::endl << std::endl << std::endl;
    tokenizeNode(root, TOKEN_TYPE::L_DELIMETER);
    //std::cout << tokenNodeToString(root, true) << std::endl << std::endl << std::endl;
    tokenizeNode(root, TOKEN_TYPE::R_DELIMETER);
    std::cout << tokenNodeToString(root, true) << std::endl << std::endl << std::endl;
    //tokenizeNode(root, TOKEN_TYPE::L_CURLY_DELIMETER);
    //tokenizeNode(root, TOKEN_TYPE::R_CURLY_DELIMETER);*/

    return root;
}
