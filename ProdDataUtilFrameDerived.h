#pragma once
#include "proddatautilframe.h"
#include "DateSortedEvent.h"

wxDECLARE_EVENT(wxEVT_UPDATE_SEARCH_RESULTS, wxCommandEvent);

wxDECLARE_EVENT(wxEVT_UPDATE_DATE_SORTED_RESULTS, DateSortedEvent);

class ProdDataUtilFrameDerived : public ProdDataUtilFrameBase
{
public:
	ProdDataUtilFrameDerived();

	ProdDataUtilFrameDerived(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString);

	void OnUpdateSearchResults(wxCommandEvent&);
	
	void OnUpdateDateSortedResults(DateSortedEvent& event);
	
private:

	wxDECLARE_EVENT_TABLE();
};
