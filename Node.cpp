#include "Classes.h"

void * Node::operator new(size_t size){
    if (Collector::getInstance()->isEmpty()){
        void * ptr = malloc(size);
        return ptr;
    }
    else{
        void * ptr = (void*) Collector::getInstance()->getRecyclableNodes()->getHead();
        Collector::getInstance()->updateRecyclableNodes();
        return ptr;
    }
}

void Node::operator delete (void * ptr){
    log(ptr);
    Collector::getInstance()->proccessNode(ptr);
}

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
