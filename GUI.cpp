#include "Classes.h"

DECLARE_APP(App)
IMPLEMENT_APP(App)
bool App::OnInit(){
    if(!wxApp::OnInit()){
        return false;
    }
    MainWindow::getInstance();
    MainWindow::getInstance()->Show(true);
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
    m_list = new List();

    SetMinSize(GetSize());
    SetMaxSize(GetSize());

    m_mainBox = new wxBoxSizer(wxVERTICAL);
    m_mainGrid = new wxFlexGridSizer(3, 1, 5, 5);

    m_topHBox = new wxBoxSizer(wxHORIZONTAL);

    m_entryAdd = new wxTextCtrl(this, wxWindow::NewControlId(), "", wxDefaultPosition, wxSize(250, 34));
    m_entryDelete = new wxTextCtrl(this, wxWindow::NewControlId(), "", wxDefaultPosition, wxSize(250, 34));

    m_buttonAdd = new wxButton(this, wxWindow::NewControlId(), "ADD");
    m_buttonAdd->Bind(wxEVT_BUTTON, &MainWindow::addButtonClicked, this);

    m_buttonDelete = new wxButton(this, wxWindow::NewControlId(), "DELETE");
    m_buttonDelete->Bind(wxEVT_BUTTON, &MainWindow::deleteButtonClicked, this);

    m_topHBox->Add(m_entryAdd);
    m_topHBox->AddSpacer(10);
    m_topHBox->Add(m_buttonAdd);
    m_topHBox->AddSpacer(34);
    m_topHBox->Add(m_entryDelete);
    m_topHBox->AddSpacer(10);
    m_topHBox->Add(m_buttonDelete);

    m_centerHBox = new wxBoxSizer(wxHORIZONTAL);

    m_centerHBox->Add(new wxStaticText(this, MainWindow::NewControlId(), "List"));
    m_centerHBox->AddSpacer(355);
    m_centerHBox->Add(new wxStaticText(this, MainWindow::NewControlId(), "Collector"));

    m_bottomHbox = new wxBoxSizer(wxHORIZONTAL);
    m_bottomGrid = new wxGridSizer(1, 2, 5, 150);
    m_listVBox = new wxBoxSizer(wxVERTICAL);
    m_collectorVBox = new wxBoxSizer(wxVERTICAL);

    m_bottomGrid->Add(m_listVBox);
    m_bottomGrid->Add(m_collectorVBox);

    m_mainGrid->Add(m_topHBox);
    m_mainGrid->Add(m_centerHBox);
    m_mainGrid->Add(m_bottomGrid);

    m_bottomHbox->AddSpacer(10);
    m_bottomHbox->Add(m_mainGrid);

    m_mainBox->AddSpacer(20);
    m_mainBox->Add(m_bottomHbox, 1, wxEXPAND);

    SetSizer(m_mainBox);
}

void MainWindow::addButtonClicked(wxCommandEvent & e) {
    if(m_entryAdd->GetValue() != "" && m_entryAdd->GetValue().IsNumber()){
        m_list->add(wxAtoi(m_entryAdd->GetValue()));
        updateLists();
    }
}

void MainWindow::deleteButtonClicked(wxCommandEvent & e) {
    if(m_entryDelete->GetValue() != "" && m_entryDelete->GetValue().IsNumber()) {
        m_list->deleteItem(wxAtoi(m_entryDelete->GetValue()));
        updateLists();
    }
}

void MainWindow::updateLists() {
    this->Freeze();

    m_listVBox->Clear(true);
    m_collectorVBox->Clear(true);

    for (int i = 0; i < m_list->getLength(); ++i) {
        Node *node = m_list->getNode(i);

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

        m_listVBox->Add(container);
        m_listVBox->AddSpacer(15);
    }

    for (int i = 0; i < Collector::getInstance()->getRecyclableNodes()->getLength(); ++i) {
        Node *node = Collector::getInstance()->getRecyclableNodes()->getNode(i);

        const void * address = static_cast<const void*>(node);
        std::stringstream addressSS;
        addressSS << address;
        std::string addressString = addressSS.str();

        wxGridSizer *container = new wxGridSizer(1, 2,5,5);
        container->Add(new wxStaticText(this, MainWindow::NewControlId(), addressString));

        m_collectorVBox->Add(container);
        m_collectorVBox->AddSpacer(15);
    }
    this->Layout();
    this->Thaw();
}
