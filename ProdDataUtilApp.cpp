// ProdDataUtilApp.cpp : Defines the entry point for the application.
//

#include "ProdDataUtilApp.h"
#include "framework.h"
#include "ProdDataUtilFrame.h"

bool ProdDataUtilApp::OnInit()
{
	// Initialize the application
    if (!wxApp::OnInit())
        return false;

    auto frame = new ProdDataUtilFrame();
    frame->Show();
    return true;
}

