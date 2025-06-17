#include "DateSortedEvent.h"
#include "ProdDataUtilFrameDerived.h"

wxDEFINE_EVENT(wxEVT_UPDATE_DATE_SORTED_RESULTS, DateSortedEvent);

DateSortedEvent::DateSortedEvent(const std::shared_ptr<DateTable>& table)
	: wxCommandEvent(wxEVT_UPDATE_DATE_SORTED_RESULTS)
	, m_table(table)
{
	
}

DateSortedEvent::~DateSortedEvent()
{
	const int x = 10;
}

std::shared_ptr<DateTable> DateSortedEvent::GetData() const
{
	return m_table;
}

wxEvent* DateSortedEvent::Clone() const
{
	return new DateSortedEvent(m_table);
}
