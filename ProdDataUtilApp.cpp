// ProdDataUtilApp.cpp : Defines the entry point for the application.
//

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

int ProdDataUtilApp::OnExit()
{
	auto searchManager = SearchManager::GetInstance();
	auto products = searchManager->GetProducts();
	for (const auto& product : products)
	{
		auto id = product->GetId();
	}
	searchManager->Clear();
	return wxApp::OnExit();
}

