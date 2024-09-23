#include <stdexcept>
#include <iostream>

template <typename T>
struct LLNode {
    T *data;
    LLNode<T> *next;
    LLNode<T> *prev;
};

template <typename T>
void replace(LLNode<T> *replaced, LLNode<T> *replacement) {
    if (replaced == nullptr) {
        throw std::runtime_error("The replaced node cannot be null.");
    }

    if (replacement == nullptr) {
        throw std::runtime_error("The replacement node cannot be null.");
    }

    // record old state
    LLNode<T> *oldPrev = replaced->prev;
    LLNode<T> *oldNext = replaced->next;

    // replace previous
    replacement->prev = oldPrev;

    // replace next
    LLNode<T> *currNode = replacement;

    while (currNode->next != nullptr) {
        currNode = currNode->next;
    }

    currNode->next = oldNext;
    
    // connect to replacement
    if (oldPrev != nullptr) {
        oldPrev->next = replacement;
    } else {
        *replaced = *replacement;
    }
    
    if (oldNext != nullptr) {
        oldNext->prev = replacement;
    }
}

template <typename T>
void print(LLNode<T> *head) {
    LLNode<T> *current = head;
    
    // Traverse through the linked list
    while (current != nullptr) {
        if (current->data != nullptr) {
            std::cout << *(current->data) << "\n";
        } else {
            std::cout << "null\n";
        }
        
        current = current->next;
    }
    
    std::cout << std::endl;
}