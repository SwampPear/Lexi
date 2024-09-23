#include <sstream>
#include <memory>
#include <map>
#include <regex>


template <typename T>
struct LLNode {
    T *data;

};

std::string tokenNodeToString(TokenNode *node, bool srcDisplay) {
    std::stringstream ss;

    while(node != nullptr) {
        // this node
        ss << "<" << tokenNames.at(node->tokenType) << " ";
        ss << node->start << " ";
        ss << node->end << ">";
        ss << " -> ";

        // next node
        if (node->prev == nullptr) {
            ss << "<nullptr> ";
        } else {
            ss << "<" << tokenNames.at(node->prev->tokenType) << " ";
            ss << node->prev->start << " ";
            ss << node->prev->end << "> ";
        }
        
        // next node
        if (node->next == nullptr) {
            ss << "<nullptr>";
        } else {
            ss << "<" << tokenNames.at(node->next->tokenType) << " ";
            ss << node->next->start << " ";
            ss << node->next->end << ">";
        }

        ss << "\n";

        if (srcDisplay) {
            std::string src = *node->src;
            std::string srcInd = src.substr(node->start, node->end - node->start);

            ss << srcInd << std::endl;
        }

        node = node->next;
    }

    std::string output = ss.str();

    return output;
}

void tokenizeContentNode(TokenNode *node, TOKEN_TYPE tokenType) {
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
}


void tokenizeNode(TokenNode *node, TOKEN_TYPE tokenType) {
    TokenNode *currNode = node;

    while (currNode != nullptr) {
        if (currNode->tokenType == TOKEN_TYPE::CONTENT) {
            tokenizeContentNode(currNode, tokenType);
            std::cout << tokenNodeToString(node, true) << std::endl << std::endl << std::endl;
        }

        currNode = currNode->next;
    }
}


TokenNode *tokenize(std::string *srcContents) {
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
    //tokenizeNode(root, TOKEN_TYPE::R_CURLY_DELIMETER);

    return root;
}
