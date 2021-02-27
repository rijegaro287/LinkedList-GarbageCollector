#include <iostream>
#include "List.h"


int main() {
    List* list = new List();

    list->add(0);
    list->add(1);
    list->add(2);
    list->add(3);
    list->add(4);
    list->add(5);

    list->printList();
}
