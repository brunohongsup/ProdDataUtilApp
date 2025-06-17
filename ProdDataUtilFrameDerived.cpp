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
	m_gridProduct->SetColLabelValue(0, "Date");
	m_gridProduct->SetColLabelValue(1, "ID");
	m_gridProduct->SetColLabelValue(2, "Judge");

	m_gridTotalCount->SetColLabelValue(0, "Total");
	m_gridTotalCount->SetColLabelValue(1, "OK");
	m_gridTotalCount->SetColLabelValue(2, "NG");

	m_tree_ctrlProduct->AddRoot(_T("IMAGE"));

	auto initiateSearch  = [this](wxCommandEvent&)
	{
		auto searchManager = SearchManager::GetInstance();
		searchManager->Clear();
		
		auto search = [this]()
		{
			auto searchManager = SearchManager::GetInstance();
			wxDateTime begin = m_date_pickerBegin->GetValue();
			wxDateTime end = m_date_pickerEnd->GetValue();
			end.SetHour(23);
			end.SetMinute(59);
			end.SetSecond(59);
			searchManager->Search(begin, end);

			auto pEvtHandler = GetEventHandler();
			auto event = new wxCommandEvent(wxEVT_UPDATE_SEARCH_RESULTS);
			pEvtHandler->QueueEvent(event);

			wxDateTime day = begin;
			wxTimeSpan oneDay(24, 0, 0, 0);

			wxTimeSpan length = end - begin;
			int nDays = length.GetDays();
			std::shared_ptr<std::vector<std::vector<std::shared_ptr<Product>>>> productsByDay = std::make_shared<std::vector<std::vector<std::shared_ptr<Product>>>>();
			productsByDay->reserve(nDays);
			auto products = searchManager->GetProducts();
			while (day <= end)
			{
				auto datePredicate = [day](const std::shared_ptr<Product>& product)
				{
					auto productTimeStamp = product->GetTimeStamp();
					if (day.GetDay() == productTimeStamp.GetDay() &&
						day.GetMonth() == productTimeStamp.GetMonth() &&
						day.GetYear() == productTimeStamp.GetYear())
						return true;

					return false;
				};

				std::vector<std::shared_ptr<Product>> productsOfDay{};
				std::copy_if(std::begin(products), std::end(products), std::back_inserter(productsOfDay), datePredicate);
				if (!productsOfDay.empty())
					productsByDay->emplace_back(std::move(productsOfDay));
				
				day += oneDay;
			}

			auto dateSortedEvent = new DateSortedEvent(productsByDay);
			pEvtHandler->QueueEvent(dateSortedEvent);
		};

		std::thread t(search);
		t.detach();
	};
	
	m_btnSearch->Bind(wxEVT_BUTTON, initiateSearch);
	Bind(wxEVT_UPDATE_SEARCH_RESULTS, &ProdDataUtilFrameDerived::OnUpdateSearchResults, this);
	Bind(wxEVT_UPDATE_DATE_SORTED_RESULTS, &ProdDataUtilFrameDerived::OnUpdateDateSortedResults, this);
}

void ProdDataUtilFrameDerived::OnUpdateSearchResults(wxCommandEvent&)
{
	auto searchManager = SearchManager::GetInstance();
	std::vector<std::shared_ptr<Product>> products = searchManager->GetProducts();
	m_gridProduct->ClearGrid();

	wxTreeItemId rootId = m_tree_ctrlProduct->GetRootItem();
	m_tree_ctrlProduct->DeleteChildren(rootId);
	
	const int rowSize = m_gridProduct->GetNumberRows();
	if (rowSize < products.size())
		m_gridProduct->AppendRows(products.size() - rowSize);

	auto findOrAddChild = [this](wxTreeItemId parent, const std::shared_ptr<Product>& product)
	{
		//ToDo Implement Here
		wxTreeItemIdValue cookie;
		wxTreeItemId child = m_tree_ctrlProduct->GetFirstChild(parent, cookie);
		while (child.IsOk()) {
			if (tree->GetItemText(child) == text)
				return child;
			child = tree->GetNextChild(parent, cookie);
		}
		return tree->AppendItem(parent, text);
	};

	for (size_t row = 0; row < products.size(); row++)
	{
		int colIdx = 0;
		auto product = products.at(row);
		m_gridProduct->SetCellValue(row, colIdx++, product->GetTimeStamp().FormatISODate());
		m_gridProduct->SetCellValue(row, colIdx++, product->GetId());
		m_gridProduct->SetCellValue(row, colIdx++, product->GetJudge());
		auto timeStamp = product->GetTimeStamp();
		int year = timeStamp.GetYear();
		int month = timeStamp.GetMonth();
		int day = timeStamp.GetDay();
		wxTreeItemIdValue cookie;
		findOrAddChild(rootId, product);		
	}
}

void ProdDataUtilFrameDerived::OnUpdateDateSortedResults(DateSortedEvent& event)
{
	auto table = event.GetData();
	const int rowSize = m_gridTotalCount->GetNumberRows();
	if (rowSize < table->size())
		m_gridTotalCount->AppendRows(table->size() - rowSize);

	for (size_t row = 0; row < table->size(); row++)
	{
		auto productsOfDay = table->at(row);
		int okCount = 0;
		int ngCount = 0;
		int naCount = 0;
		for (size_t idx = 0; idx < productsOfDay.size(); idx++)
		{
			auto product = productsOfDay.at(idx);
			if (product->GetJudge() == _T("OK"))
				okCount++;

			else if (product->GetJudge() == _T("NG"))
				ngCount++;

			else
				naCount++;
		}

		auto product = productsOfDay.at(0);
		m_gridTotalCount->SetRowLabelValue(row, product->GetTimeStamp().FormatISODate());
		m_gridTotalCount->SetCellValue(row, 0, wxString::Format("%08d", (int)productsOfDay.size()));
		m_gridTotalCount->SetCellValue(row, 1, wxString::Format("%08d", okCount));
		m_gridTotalCount->SetCellValue(row, 2, wxString::Format("%08d", ngCount));
	}
}
