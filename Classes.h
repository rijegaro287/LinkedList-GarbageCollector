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
    void * operator new(size_t size); //Valida si Collector tiene nodos disponibles para reciclar y los utiliza, en caso contrario, crea un nodo nuevo
    void operator delete (void * ptr); //Envía el nodo a la lista de Collector
    Node(int data);
    int getData(); //Retorna el valor que guarda el nodo
    Node* getNext(); //Retorna un puntero al siguiente nodo
    void setData(int valor); //Cambia el valor que guarda el nodo
    void setNext(Node* next); //Cambia el puntero al siguiente nodo
};

class List {
private:
    Node *m_head;
    int m_length;
public:
    List();
    void add(int data); //Añade un nuevo nodo con el valor ingresado al inicio de la lista
    void addNode(Node* node); //Añade un nodo pre-existene al inicio de la lista
    void deleteItem (int index); //Elimina el nodo que esté en la posición ingresada
    Node* getNode(int index); //Retorna un puntero al nodo que esté en la posición ingresada
    Node* getHead(); //Retorna un puntero al primer elemento de la lista
    void setHead(Node* head); //Cambia el puntero al primer elemento de la lista
    int getLength(); //Retorna el tamaño de la lista
    void setLength(int length); //Cambia el tamaño de la lista
    void printList(); //Imprime los valores de todos los nodos de List
    void printListAddresses(); //Imprime las direcciones de memoria de todos los nodos de la lista
};

class Collector{
private:
    List *m_recyclableNodes = nullptr;
    List *tmpList = nullptr;
    static Collector *m_collectorInstance;
    Collector();
public:
    static Collector* getInstance(); //Retorna una instancia única de Collector (singleton)
    void proccessNode(void * nodePtr); //Recibe un nodo cuyos atributos se borran y es agregado a la lista de Collector
    void updateRecyclableNodes(); //Actualiza la lista de Collector luego de que un nodo es reutilizado
    bool isEmpty(); //Retorna true si no hay elementos en la lista de Collector, de lo contrario retorna false
    List* getRecyclableNodes(); //Retorna la lista con todos los nodos de Collector
};

class App: public wxApp{
public:
    virtual bool OnInit(); //Inicializa la aplicación
};

class MainWindow : public wxFrame{
private:
    List *m_list;
    wxBoxSizer *m_mainBox;
    wxFlexGridSizer *m_mainGrid;
    wxBoxSizer *m_topHBox;
    wxBoxSizer *m_centerHBox;
    wxBoxSizer *m_bottomHbox;
    wxGridSizer *m_bottomGrid;
    wxBoxSizer *m_listVBox;
    wxBoxSizer *m_collectorVBox;
    wxTextCtrl *m_entryAdd;
    wxTextCtrl *m_entryDelete;
    wxButton *m_buttonAdd;
    wxButton *m_buttonDelete;
    static MainWindow *m_mainWindowInstance;
    MainWindow(wxWindow *parent,
               wxWindowID id,
               const wxString& title,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxASCII_STR(wxFrameNameStr));
public:
    static MainWindow* getInstance(); //Retorna una instancia única de MainWindow (singleton)
    void addButtonClicked(wxCommandEvent & e); //Agrega un nodo a List y actualiza la interfaz
    void deleteButtonClicked(wxCommandEvent & e);//Borra un nodo de List y actualiza la interfaz
    void updateLists(); //Actualiza la interfaz con los contenidos de List y Collector
};
