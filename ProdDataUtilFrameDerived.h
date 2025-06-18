#pragma once
#include "proddatautilframe.h"
#include "DateSortedEvent.h"
#include <wx/file.h>
#include <wx/filename.h>

wxDECLARE_EVENT(wxEVT_UPDATE_SEARCH_RESULTS, wxCommandEvent);

wxDECLARE_EVENT(wxEVT_UPDATE_DATE_SORTED_RESULTS, DateSortedEvent);

class ProdDataUtilFrameDerived : public ProdDataUtilFrameBase
{
public:
	ProdDataUtilFrameDerived();

	ProdDataUtilFrameDerived(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString);

	void OnUpdateSearchResults(wxCommandEvent&);
	
	void OnUpdateDateSortedResults(DateSortedEvent& event);

	// In your header file (likely ProdDataUtilFrameDerived.h)
	void OnTreeItemSelected(wxTreeEvent& event);
	
	void OnLeafNodeClicked(const Product& product);

	// Helper method to check if item is leaf
	bool IsLeafNode(wxTreeItemId item) const;

private:

	void HighlightProductInGrid(const Product& product) const;

	wxDECLARE_EVENT_TABLE();
};
