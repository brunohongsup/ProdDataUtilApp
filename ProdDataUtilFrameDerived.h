#pragma once
#include "proddatautilframe.h"

wxDECLARE_EVENT(wxEVT_UPDATE_SEARCH_RESULTS, wxCommandEvent);

class ProdDataUtilFrameDerived : public ProdDataUtilFrameBase
{
public:
	ProdDataUtilFrameDerived();

	ProdDataUtilFrameDerived(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString);

	void OnUpdateSearchResults(wxCommandEvent&);
	
private:

	wxDECLARE_EVENT_TABLE();
};
