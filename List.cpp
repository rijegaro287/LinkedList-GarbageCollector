#include "Classes.h"

List::List() {
    m_head = nullptr;
    m_length = 0;
}

void List::add(int data){
    if(m_head == nullptr){
        m_head = new Node(data);
    }
    else{
        Node *newHead = new Node(data);
        newHead->setNext(m_head);
        m_head = newHead;
    }
    m_length++;
}

void List::addNode(Node* node){
    if(m_head == nullptr){
        m_head = node;
    }
    else{
        node->setNext(m_head);
        m_head = node;
    }
    m_length++;
}

void List::deleteItem (int index){
    if(m_length == 0){
        log("Error: empty m_list");
        return;
    }
    else if (index >= m_length){
        log("Error: index >= length");
        return;
    }
    else{
        if(index == 0){
            Node* newHead = m_head->getNext();
            delete m_head;
            m_head = newHead;
        }
        else{
            Node* tmp = m_head;
            int stopIndex = index - 1;
            for(int i = 0; i != stopIndex ; i++){
                tmp = tmp->getNext();
            }
            if (index == m_length){
                delete tmp->getNext();
                tmp->setNext(nullptr);
            }
            else{
                Node* newNext = tmp->getNext()->getNext();
                delete tmp->getNext();
                tmp->setNext(newNext);
            }
        }
    }
    m_length--;
}

Node* List::getNode(int index){
    if(m_length == 0){
        log("Error: empty m_list");
        return nullptr;
    }
    else if (index >= m_length){
        log("Error: index >= length");
        return nullptr;
    }
    else{
        if(index == 0){
            return m_head;
        }
        else{
            Node* tmp = m_head;
            for(int i = 0; i != index ; i++){
                tmp = tmp->getNext();
            }
            return tmp;
        }
    }
}

Node* List::getHead(){
    return m_head;
}

void List::setHead(Node* head){
    m_head = head;
}

int List::getLength(){
    return m_length;
}

void List::setLength(int length){
    m_length = length;
}

void List::printList(){
    if (m_length > 0){
        Node* tmp = m_head;
        while (tmp != nullptr){
            log(tmp->getData());
            tmp = tmp->getNext();
        }
    }
}

void List::printListAddresses(){
    if (m_length > 0){
        Node* tmp = m_head;
        while (tmp != nullptr){
            log(tmp);
            tmp = tmp->getNext();
        }
    }
}


