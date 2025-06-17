#pragma once
#include <wx/event.h>
#include "Product.h"

using DateTable = std::vector<std::vector<std::shared_ptr<Product>>>;

class DateSortedEvent : public wxCommandEvent
{
public:
	DateSortedEvent(const std::shared_ptr<DateTable>& table = nullptr);

	~DateSortedEvent();

	std::shared_ptr<DateTable> GetData() const;

	wxEvent* Clone() const override;

private:
	std::shared_ptr<DateTable> m_table;	
};
