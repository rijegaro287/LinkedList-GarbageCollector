#pragma once
#include <iostream>
#include <wx/wx.h>
#include <sstream>
#include <string>
#define log(message) std::cout<<message<<std::endl;

class Node {
private:
    Node *m_next;
    int m_data;
public:
    void * operator new(size_t size);
    void operator delete (void * ptr);
    Node(int data);
    int getData();
    Node* getNext();
    void setData(int valor);
    void setNext(Node* next);
};

class List {
private:
    Node *m_head;
    int m_length;
public:
    List();
    void add(int data);
    void addNode(Node* node);
    void deleteItem (int index);
    Node* getNode(int index);
    void modifyValue(int index, int value);
    void switchValues(int index1, int index2);
    Node* getHead();
    void setHead(Node* head);
    int getLength();
    void setLength(int length);
    void printList();
    void printListAddresses();
};

class Collector{
private:
    List *m_recyclableNodes = nullptr;
    List *tmpList = nullptr;
    static Collector *m_collectorInstance;
    Collector();
public:
    static Collector* getInstance();
    void proccessNode(void * nodePtr);
    void updateRecyclableNodes();
    bool isEmpty();
    List* getRecyclableNodes();
};

class App: public wxApp{
public:
    virtual bool OnInit();
};

class MainWindow : public wxFrame{
private:
    static MainWindow *m_mainWindowInstance;
    MainWindow(wxWindow *parent,
               wxWindowID id,
               const wxString& title,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxASCII_STR(wxFrameNameStr));
public:
    static MainWindow* getInstance();
    void addButtonClicked(wxCommandEvent & e);
    void deleteButtonClicked(wxCommandEvent & e);
    void updateLists();
};
