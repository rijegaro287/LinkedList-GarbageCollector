#include <iostream>
#include "Classes.h"

int main() {
    List *list = new List();
    list->add(0);
    list->add(1);
    list->add(2);
    list->add(3);
    list->add(4);
    list->add(5);
    list->printListAddresses();

    log("borrados -----------------------");
    list->deleteItem(0);
    list->deleteItem(0);
    list->deleteItem(0);
    list->deleteItem(0);
    list->deleteItem(0);
    list->deleteItem(0);

    log("reciclados -----------------------");
    Collector::getInstance()->getRecyclableNodes()->printListAddresses();

    list->add(6);
    list->add(7);
    list->add(8);
    list->add(9);
    list->add(10);
    list->add(11);
    list->add(12);
    list->add(13);
    list->add(14);
    list->add(15);

    log("actualizada -----------------------------");
    Collector::getInstance()->getRecyclableNodes()->printListAddresses();

    log("nuevos ------------------------------");
    list->printListAddresses();

    log("valores --------------------------------");
    list->printList();

}
