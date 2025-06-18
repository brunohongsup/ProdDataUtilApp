// ProdDataUtilApp.cpp : Defines the entry point for the application.
//

#define _CRT_SECURE_NO_WARNINGS

#include "ProdDataUtilApp.h"
#include "framework.h"
#include "proddatautilframe.h"
#include "ProdDataUtilFrameDerived.h"
#include "SearchManager.h"

wxIMPLEMENT_APP(ProdDataUtilApp);

bool ProdDataUtilApp::OnInit()
{
	// Initialize the application
    if (!wxApp::OnInit())
        return false;

	wxInitAllImageHandlers();

    const auto frame = new ProdDataUtilFrameDerived(nullptr, wxID_ANY, "ProdDataUtilApp");
	frame->Show();
    return true;
}
