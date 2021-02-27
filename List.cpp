#include "List.h"

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

void List::deleteItem (int index){
    if(m_length == 0){
        log("Error: empty list");
        return;
    }
    else if (index > m_length){
        log("Error: index > length");
        return;
    }
    else{
        if(index == 0){
            Node* newHead = m_head->getNext();
            delete m_head;
            m_head = nullptr;
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
                tmp->setNext(nullptr);
                tmp->setNext(newNext);
            }
        }
    }
    m_length--;
}

Node* List::getNode(int index){
    if(m_length == 0){
        log("Error: empty list");
        return nullptr;
    }
    else if (index > m_length){
        log("Error: index > length");
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

void List::modifyValue(int index, int value){
    getNode(index)->setData(value);
}

void List::switchValues(int index1, int index2){
    if (m_length == 0){
        log("Error: empy list");
        return;
    }
    else if(index1 > m_length || index2 > m_length){
        log("Error: index out of range");
        return;
    }
    else if(index1 == index2){
        log("Error: indexes can't be the same");
        return;
    }
    else{
        Node item1Copy = *getNode(index1);
        Node* item1 = getNode(index1);
        Node* item2 = getNode(index2);
        item1->setData(item2->getData());
        item2->setData(item1Copy.getData());
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
};

void List::printList(){
    if (m_length > 0){
        Node* tmp = m_head;
        while (tmp != nullptr){
            log(tmp->getData());
            tmp = tmp->getNext();
        }
    }
}


