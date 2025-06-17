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
			std::vector<std::vector<std::shared_ptr<Product>>> productsByDay{};
			productsByDay.reserve(nDays);
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
					productsByDay.emplace_back(std::move(productsOfDay));
				
				day += oneDay;
			}

			
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
	auto products = searchManager->GetProducts();
	m_gridProduct->ClearGrid();
	const int rowSize = m_gridProduct->GetNumberRows();
	if (rowSize < products.size())
		m_gridProduct->AppendRows(products.size() - rowSize);

	for (size_t row = 0; row < products.size(); row++)
	{
		int colIdx = 0;
		auto product = products.at(row);
		m_gridProduct->SetCellValue(row, colIdx++, product->GetTimeStamp().FormatISODate());
		m_gridProduct->SetCellValue(row, colIdx++, product->GetId());
		m_gridProduct->SetCellValue(row, colIdx++, product->GetJudge());
	}
}

void ProdDataUtilFrameDerived::OnUpdateDateSortedResults(DateSortedEvent& event)
{
	
}
