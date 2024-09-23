#include <cstdlib>
#include <stdexcept>
#include <string>
#include <cassert>
#include <iostream>
#include "linked_list.hpp"

void test_links_head() {
    std::cout << "insert at head" << std::endl;
    // list 1
    LLNode<int> *head1 = testList(0, 5);

    // list 1
    LLNode<int> *head2 = testList(10, 10);
    replace(head1, head2);

    print(head1);
}

void test_links_middle() {
    std::cout << "insert at middle" << std::endl;
    // list 1
    LLNode<int> *head1 = testList(0, 5);

    // list 1
    LLNode<int> *head2 = testList(10, 10);
    replace(head1->next->next, head2);

    print(head1);
}

void test_links_last() {
    std::cout << "insert at end" << std::endl;
    // list 1
    LLNode<int> *head1 = testList(0, 5);

    // list 1
    LLNode<int> *head2 = testList(10, 10);
    replace(head1->next->next->next->next, head2);

    print(head1);
}

int main() {
    test_links_head();
    test_links_middle();
    test_links_last();
    // list 1
    //LLNode<int> *head1 = testList(0, 7);

    // list 2
    //LLNode<int> *head2 = testList(10, 10);

    //replace(head1->next->next->next->next->next, head2);

    //print(head1);

    return EXIT_SUCCESS;
}