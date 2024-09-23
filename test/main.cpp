#include <cstdlib>
#include <stdexcept>
#include <string>
#include <cassert>
#include <iostream>
#include "linked_list.hpp"


int main() {
    test_insert_at_head();
    test_insert_in_middle();
    test_insert_at_end();
    test_single_insert_at_head();
    test_single_insert_in_middle();
    test_single_insert_at_end();

    // list 1
    //LLNode<int> *head1 = testList(0, 7);

    // list 2
    //LLNode<int> *head2 = testList(10, 10);

    //replace(head1->next->next->next->next->next, head2);

    //print(head1);

    return EXIT_SUCCESS;
}