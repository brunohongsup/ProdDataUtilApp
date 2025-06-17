#include "ProdDataUtilFrameDerived.h"
#include"ProdDataUtilApp.h"
#include "SearchManager.h"
wxDEFINE_EVENT(wxEVT_UPDATE_SEARCH_RESULTS, wxCommandEvent);
	
wxBEGIN_EVENT_TABLE(ProdDataUtilFrameDerived, wxFrame)
wxEND_EVENT_TABLE()

ProdDataUtilFrameDerived::ProdDataUtilFrameDerived()
	: ProdDataUtilFrameBase()
{
	
}

ProdDataUtilFrameDerived::ProdDataUtilFrameDerived(wxWindow* parent, wxWindowID id, const wxString& title)
	: ProdDataUtilFrameBase(parent, id, title, wxDefaultPosition, wxSize(800, 600))
{
	m_grid->SetColLabelValue(0, "Date");
	m_grid->SetColLabelValue(1, "ID");
	m_grid->SetColLabelValue(2, "Judge");

	auto initiateSearch  = [this](wxCommandEvent&)
	{
		auto searchManager = SearchManager::GetInstance();
		searchManager->Clear();
		
		auto begin = m_date_pickerBegin->GetValue();
		auto end = m_date_pickerEnd->GetValue();
		searchManager->Search(begin, end);

		auto pEvtHandler = GetEventHandler();
		auto event = new wxCommandEvent(wxEVT_UPDATE_SEARCH_RESULTS);
		pEvtHandler->QueueEvent(event);
	};
	
	m_btnSearch->Bind(wxEVT_BUTTON, initiateSearch);
	Bind(wxEVT_UPDATE_SEARCH_RESULTS, &ProdDataUtilFrameDerived::OnUpdateSearchResults, this);
}

void ProdDataUtilFrameDerived::OnUpdateSearchResults(wxCommandEvent&)
{
	auto searchManager = SearchManager::GetInstance();
	auto products = searchManager->GetProducts();
	m_grid->ClearGrid();
	const int rowSize = m_grid->GetNumberRows();
	if (rowSize < products.size())
		m_grid->AppendRows(products.size() - rowSize);

	for (size_t row = 0; row < products.size(); row++)
	{
		int colIdx = 0;
		auto product = products.at(row);
		m_grid->SetCellValue(row, colIdx++, product->GetTimeStamp().FormatISODate());
		m_grid->SetCellValue(row, colIdx++, product->GetId());
		m_grid->SetCellValue(row, colIdx++, product->GetJudge());
	}
	
}
