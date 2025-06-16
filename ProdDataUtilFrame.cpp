#include <wx/wx.h>
#include <wx/msw/menu.h>
#include "ProdDataUtilFrame.h"

wxIMPLEMENT_APP(ProdDataUtilApp);

ProdDataUtilFrame::ProdDataUtilFrame()
    : wxFrame(nullptr, wxID_ANY, "ProdDataUtilApp")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl+H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &ProdDataUtilFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &ProdDataUtilFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &ProdDataUtilFrame::OnAbout, this, wxID_ABOUT);
}

void ProdDataUtilFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void ProdDataUtilFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void ProdDataUtilFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                "About Hello World", wxOK | wxICON_INFORMATION);
}
