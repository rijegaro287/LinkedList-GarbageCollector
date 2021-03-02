#include "Classes.h"

DECLARE_APP(App)
IMPLEMENT_APP(App)

enum ids{
    MAIN_WINDOW = wxID_HIGHEST + 1
};

bool App::OnInit(){
    if(!wxApp::OnInit()){
        return false;
    }
    MainWindow *mainWindow = new MainWindow(nullptr, ids::MAIN_WINDOW, "Main Window");
    mainWindow->Show();
    return true;
}

MainWindow::MainWindow(wxWindow *parent,
                       wxWindowID id,
                       const wxString& title,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style,
                       const wxString& name) : wxFrame(parent, id, title, pos, size, style){
}

