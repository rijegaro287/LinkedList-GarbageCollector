#include "Node.h"

Node::Node(int data){
    m_next = nullptr;
    m_data = data;
}

int Node::getData(){
    return m_data;
}

Node* Node::getNext(){
    return m_next;
}

void Node::setData(int valor){
    m_data = valor;
}

void Node::setNext(Node* next){
    m_next = next;
}
