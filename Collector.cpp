#include "Classes.h"

Collector *Collector::m_collectorInstance = nullptr;

Collector::Collector() {
    m_recyclableNodes = new List();
}

Collector* Collector::getInstance(){
    if(m_collectorInstance == nullptr){
        m_collectorInstance = new Collector();
    }
    return m_collectorInstance;
}

void Collector::proccessNode(void * node){
    Node* nodePtr = (Node*) node;
    /*nodePtr->setData(0);*/
    nodePtr->setNext(nullptr);
    m_recyclableNodes->addNode(nodePtr);
}

List* Collector::getRecyclableNodes(){
    return m_recyclableNodes;
}

void Collector::updateRecyclableNodes(){
    if(m_recyclableNodes->getLength() == 1){
        m_recyclableNodes = new List();
    }
    else{
        tmpList = new List();
        tmpList->addNode(m_recyclableNodes->getHead()->getNext());
        tmpList->setLength(m_recyclableNodes->getLength() - 1);
        delete m_recyclableNodes;
        m_recyclableNodes = tmpList;
    }
}

bool Collector::isEmpty() {
    if(m_recyclableNodes->getLength() == 0){
        return true;
    }
    else{
        return false;
    }
}
