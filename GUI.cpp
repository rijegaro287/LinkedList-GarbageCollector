#include "Classes.h"

DECLARE_APP(App)
IMPLEMENT_APP(App)

List *list;

wxBoxSizer *mainBox;
wxFlexGridSizer *mainGrid;
wxBoxSizer *topHBox;
wxBoxSizer *centerHBox;
wxBoxSizer *bottomHbox;
wxGridSizer *bottomGrid;
wxBoxSizer *listVBox;
wxBoxSizer *collectorVBox;
wxTextCtrl *entryAdd;
wxTextCtrl *entryDelete;
wxButton *buttonAdd;
wxButton *buttonDelete;

bool App::OnInit(){
    if(!wxApp::OnInit()){
        return false;
    }
    MainWindow::getInstance();
    MainWindow::getInstance()->Show(true);
    list = new List();
    return true;
}

MainWindow *MainWindow::m_mainWindowInstance = nullptr;

MainWindow* MainWindow::getInstance() {
    if(m_mainWindowInstance == nullptr){
        m_mainWindowInstance = new MainWindow(nullptr, wxWindow::NewControlId(), "List Collector", wxPoint(0, 0), wxSize(800, 600));
    }
    return m_mainWindowInstance;
}

MainWindow::MainWindow(wxWindow *parent,
                       wxWindowID id,
                       const wxString& title,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style,
                       const wxString& name) : wxFrame(parent, id, title, pos, size, style) {
    SetMinSize(GetSize());
    SetMaxSize(GetSize());

    mainBox = new wxBoxSizer(wxVERTICAL);
    mainGrid = new wxFlexGridSizer(3, 1,5, 5);

    topHBox = new wxBoxSizer(wxHORIZONTAL);

    entryAdd = new wxTextCtrl(this, wxWindow::NewControlId(), "", wxDefaultPosition, wxSize(250, 34));
    entryDelete = new wxTextCtrl(this, wxWindow::NewControlId(), "", wxDefaultPosition, wxSize(250, 34));

    buttonAdd = new wxButton(this, wxWindow::NewControlId(), "ADD");
    buttonAdd->Bind(wxEVT_BUTTON, &MainWindow::addButtonClicked, this);

    buttonDelete = new wxButton(this, wxWindow::NewControlId(), "DELETE");
    buttonDelete->Bind(wxEVT_BUTTON, &MainWindow::deleteButtonClicked, this);

    topHBox->Add(entryAdd);
    topHBox->AddSpacer(10);
    topHBox->Add(buttonAdd);
    topHBox->AddSpacer(34);
    topHBox->Add(entryDelete);
    topHBox->AddSpacer(10);
    topHBox->Add(buttonDelete);

    centerHBox = new wxBoxSizer(wxHORIZONTAL);

    centerHBox->Add(new wxStaticText(this, MainWindow::NewControlId(), "List"));
    centerHBox->AddSpacer(355);
    centerHBox->Add(new wxStaticText(this, MainWindow::NewControlId(), "Collector"));

    bottomHbox = new wxBoxSizer(wxHORIZONTAL);
    bottomGrid = new wxGridSizer(1,2,5,150);
    listVBox = new wxBoxSizer(wxVERTICAL);
    collectorVBox = new wxBoxSizer(wxVERTICAL);

    bottomGrid->Add(listVBox);
    bottomGrid->Add(collectorVBox);

    mainGrid->Add(topHBox);
    mainGrid->Add(centerHBox);
    mainGrid->Add(bottomGrid);

    bottomHbox->AddSpacer(10);
    bottomHbox->Add(mainGrid);

    mainBox->AddSpacer(20);
    mainBox->Add(bottomHbox, 1, wxEXPAND);

    SetSizer(mainBox);
}

void MainWindow::addButtonClicked(wxCommandEvent & e) {
    if(entryAdd->GetValue() != "" && entryAdd->GetValue().IsNumber()){
        list->add(wxAtoi(entryAdd->GetValue()));
        updateLists();
    }
}

void MainWindow::deleteButtonClicked(wxCommandEvent &e) {
    if(entryAdd->GetValue() != "" && entryAdd->GetValue().IsNumber()) {
        list->deleteItem(wxAtoi(entryDelete->GetValue()));
        updateLists();
    }
}

void MainWindow::updateLists() {
    this->Freeze();

    listVBox->Clear(true);
    collectorVBox->Clear(true);

    for (int i = 0; i < list->getLength(); ++i) {
        Node *node = list->getNode(i);

        std::stringstream valueSS;
        valueSS << node->getData();
        std::string valueString = valueSS.str();

        const void * address = static_cast<const void*>(node);
        std::stringstream addressSS;
        addressSS << address;
        std::string addressString = addressSS.str();

        wxGridSizer *container = new wxGridSizer(1, 2,5,5);
        container->Add(new wxStaticText(this, MainWindow::NewControlId(), valueString));
        container->Add(new wxStaticText(this, MainWindow::NewControlId(), addressString));

        listVBox->Add(container);
        listVBox->AddSpacer(15);
    }

    for (int i = 0; i < Collector::getInstance()->getRecyclableNodes()->getLength(); ++i) {
        Node *node = Collector::getInstance()->getRecyclableNodes()->getNode(i);

        const void * address = static_cast<const void*>(node);
        std::stringstream addressSS;
        addressSS << address;
        std::string addressString = addressSS.str();

        wxGridSizer *container = new wxGridSizer(1, 2,5,5);
        container->Add(new wxStaticText(this, MainWindow::NewControlId(), addressString));

        collectorVBox->Add(container);
        collectorVBox->AddSpacer(15);
    }
    this->Layout();
    this->Thaw();
}
