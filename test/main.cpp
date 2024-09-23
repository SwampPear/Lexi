#include <cstdlib>
#include <stdexcept>
#include <string>
#include "linked_list.hpp"


LLNode<int> *testList(int min, int max) {
    // node 1
    LLNode<int> *root = new LLNode<int>();
    int *data = new int(min);
    root->data = data;
    root->next = nullptr;
    root->prev = nullptr;

    // test list 1
    LLNode<int> *prevNode = root;

    for (int i = min + 1; i < max; i++) {
        LLNode<int> *newNode = new LLNode<int>();

        int *newData = new int(i);
        newNode->data = newData;

        newNode->next = nullptr;
        newNode->prev = prevNode;

        prevNode->next = newNode;
        prevNode = newNode;
    }

    return root;
}



int main() {
    // list 1
    LLNode<int> *head1 = testList(0, 7);

    // list 2
    LLNode<int> *head2 = testList(10, 10);

    replace(head1->next->next->next->next->next, head2);

    print(head1);

    return EXIT_SUCCESS;
}