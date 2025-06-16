// ProdDataUtilApp.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ProdDataUtilApp.h"

wxIMPLEMENT_APP(ProdDataUtilApp);

bool ProdDataUtilApp::OnInit()
{
	// Initialize the application
    if (!wxApp::OnInit())
        return false;

    auto frame = new wxFrame();
    frame->Show();
    return true;
}
