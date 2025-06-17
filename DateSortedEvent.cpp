#include "DateSortedEvent.h"
#include "ProdDataUtilFrameDerived.h"

wxDEFINE_EVENT(wxEVT_UPDATE_DATE_SORTED_RESULTS, DateSortedEvent);

DateSortedEvent::DateSortedEvent(int id, const std::shared_ptr<DateTable>& table)
	: wxCommandEvent(wxEVT_UPDATE_DATE_SORTED_RESULTS,id)
	, m_table(table)
{
	
}

std::shared_ptr<DateTable> DateSortedEvent::GetData() const
{
	return m_table;
}

wxEvent* DateSortedEvent::Clone() const
{
	return new DateSortedEvent(GetId(), m_table);
}
