#pragma once
#include "Node.h"
class List {
private:
    Node *m_head;
    int m_length;

public:
    List();
    void add(int data);
    void deleteItem (int index);
    Node* getNode(int index);
    void modifyValue(int index, int value);
    void switchValues(int index1, int index2);
    Node* getHead();
    void setHead(Node* head);
    int getLength();
    void printList();
};
