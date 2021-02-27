#pragma once
#include <iostream>
#define log(message) std::cout<<message<<std::endl;

class Node {
private:
    Node *m_next;
    int m_data;
public:
    Node(int data);
    int getData();
    Node* getNext();
    void setData(int valor);
    void setNext(Node* next);
};
